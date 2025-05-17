#include "server.h"
#include "packetids.h"
#include <QDataStream>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QTimeZone>

Server::Server(QObject *parent) : QObject(parent)
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::onNewConnection);
    arduinosId = new QSet<QString>();
    loadArduinosId();
    setupPinger();
}

// загрузка айдишников ардуин
void Server::loadArduinosId()
{
    QFile file("arduinos.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList parts = line.split(';');
        if(parts.length() < 2)
        {
            continue;
        }
        arduinosId->insert(parts[0]);
    }
    file.close();
}

// таймер для 'пинговки' каждые 2 сек
void Server::setupPinger()
{
    QTimer *pingTimer = new QTimer(this);
    pingTimer->setInterval(2000);
    connect(pingTimer, &QTimer::timeout, this, &Server::pingAllSockets);
    pingTimer->start();
}

void Server::pingAllSockets()
{
    for (auto it = buffers.keyValueBegin(); it != buffers.keyValueEnd(); ++it)
    {
        QTcpSocket *socket = it->first;
        sendPacketTo(socket, PacketID_PING);
    }
}

// старт сервера
void Server::start()
{
    quint16 port = 24516;
    if (tcpServer->listen(QHostAddress::Any, port))
    {
        qInfo() << "Server started on port: " + QString::number(port);
    }
    else
    {
        qCritical() << "Failed to start server: " << tcpServer->errorString();
        exit(1);
    }
}

// что-то подключилось
void Server::onNewConnection()
{
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    qInfo() << "New connection " << clientSocket->peerAddress().toString();
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &Server::onDisconnected);
    connect(clientSocket, &QTcpSocket::errorOccurred, this, &Server::onError);
    buffers[clientSocket] = QByteArray();
    QTimer *timer = new QTimer(this);
    // 5 секунд нет понга - значит клиент откис
    timer->setInterval(5000);
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, &Server::onTimeout);
    timer->start();
    clientTimers.insert(clientSocket, timer);
}

// новые данные для чтения доступны
void Server::onReadyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == nullptr)
    {
        return;
    }
    buffers[socket].append(socket->readAll());
    processBuffer(socket);
}

// сборка данных в пакет
void Server::processBuffer(QTcpSocket *socket)
{
    QByteArray &buffer = buffers[socket];
    while (true)
    {
        if (buffer.size() < PacketHeaderSize)
        {
            return;
        }
        QDataStream in(buffer);
        in.setByteOrder(QDataStream::BigEndian);
        qint32 len;
        qint8 id;
        in >> len >> id;
        if (buffer.size() < len)
        {
            return;
        }
        QByteArray payload = buffer.mid(PacketHeaderSize, len - PacketHeaderSize);
        QString str = QString::fromUtf8(payload);
        handlePacket(socket, id, str.split(";"));
        buffer = buffer.mid(len);
    }
}

// обработка пакета
void Server::handlePacket(QTcpSocket *socket, qint8 id, QStringList args)
{
    switch (id)
    {
    case PacketID_PONG: {
        // сброс таймера на кик
        clientTimers[socket]->start();
    }
    break;
    case PacketID_HELLO: {
        sendPacketTo(socket, PacketID_HI);
        if (args[0] == "IAMARDUINO")
        {
            QString arduinoId = "UINO-" + args[1];
            QString bullBitrhDate = args[2];
            socket->setObjectName(arduinoId);
            checkAndAddArduino(arduinoId, bullBitrhDate);
            broadcastToApps(PacketID_UPDATE_ROW_CELL_VALUE, arduinoId + ";Статус;" + "Подключён");
        }
        else if (args[0] == "IAMQTAPP")
        {
            socket->setObjectName("Qtapp");
            for (const QString &arduinoId : *arduinosId)
            {
                QFile file("arduinos.txt");
                file.open(QIODevice::ReadOnly | QIODevice::Text);
                QString note;
                QString bullBirthDate;
                QTextStream in(&file);
                while (!in.atEnd())
                {
                    QString line = in.readLine();
                    QStringList parts = line.split(";");
                    if (parts[0] == arduinoId)
                    {
                        bullBirthDate = parts.value(1);
                        note = parts.value(2);
                    }
                }
                QDate startDate = QDate::fromString(bullBirthDate, "dd.MM.yyyy");
                QDate currentDate = QDate::currentDate();
                int daysPassed = startDate.daysTo(currentDate);
                int monthPassed = daysPassed / 30;
                QString age = QString::number(monthPassed) + "мес. " + QString::number(daysPassed % 30) + "д.";

                QString latestTemp = "?";
                bool isLie = false;

                QFile sfile("sensor_log.txt");
                sfile.open(QIODevice::ReadOnly | QIODevice::Text);
                QTextStream s_in(&sfile);
                while (!s_in.atEnd())
                {
                    QString line = s_in.readLine();
                    QStringList parts = line.split(';');
                    QString id = parts[1];
                    QString type = parts[2];
                    QString value = parts[3];
                    if (id == arduinoId)
                    {
                        if (type == "temp" && value != "")
                        {
                            latestTemp = value + "°C";
                        }
                        else if (type == "obstacle")
                        {
                            isLie = value == "1";
                        }
                    }
                }
                sfile.close();

                QString status = isArduinoOnline(arduinoId) ? "Подключён" : "Оффлайн";
                sendPacketTo(socket, PacketID_INIT_ROW,
                             arduinoId + ";" + note + ";" + status + ";" + age + ";" + latestTemp + ";" +
                                 (isLie ? "Да" : "Нет"));
            }
        }
    }
    break;
    case PacketID_GET_FULL_INFO: {
        QString arduinoId = args[0];
        QString timeLimit = args[1];
        QString data = processSensorsLog(arduinoId, timeLimit);
        sendPacketTo(socket, PacketID_SEND_FULL_INFO, data);
    }
    break;
    case PacketID_UPDATE_SENSOR_VALUE: {
        QString arduinoId = socket->objectName();
        QString sensorType = args[0];
        QString sensorValue = args[1];
        QString timestamp = QDateTime::currentDateTime().toTimeZone(QTimeZone("Asia/Yekaterinburg")).toString(Qt::ISODate);
        QString line = timestamp + ";" + arduinoId + ";" + sensorType + ";" + sensorValue + "\n";

        QFile file("sensor_log.txt");
        if (file.open(QIODevice::Append | QIODevice::Text))
        {
            QTextStream out(&file);
            out << line;
            file.close();
        }

        if (sensorType == "temp")
        {
            broadcastToApps(PacketID_UPDATE_ROW_CELL_VALUE, arduinoId + ";Темп. помещения;" + sensorValue + "°C");
        }
        else if (sensorType == "obstacle")
        {
            broadcastToApps(PacketID_UPDATE_ROW_CELL_VALUE,
                            arduinoId + ";Лежит;" + (sensorValue == "1" ? "Да" : "Нет"));
        }
    }
    break;
    case PacketID_EDIT_NOTE: {
        QString arduinoId = args[0];
        QString newNote = args[1];
        updateArduinoNote(arduinoId, newNote);
    }
    }
}

// отправить пакет опредленному сокету
void Server::sendPacketTo(QTcpSocket *socket, qint8 id, const QString &data)
{
    // qDebug() << "Send packet " << id << " " << data;
    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);
    qint32 len = data.toUtf8().size() + PacketHeaderSize;
    out << len;
    out << id;
    packet.append(data.toUtf8());
    socket->write(packet);
    socket->flush();
}

// отправить пакет всем подключенным Qt приложениям
void Server::broadcastToApps(qint8 id, const QString &data)
{
    for (auto it = buffers.keyValueBegin(); it != buffers.keyValueEnd(); ++it)
    {
        QTcpSocket *socket = it->first;
        if (socket->objectName() == "Qtapp")
        {
            sendPacketTo(socket, id, data);
        }
    }
}

// добавить в список ардуино, если нету
void Server::checkAndAddArduino(QString &arduinoId, QString &bullBirthDate)
{
    QFile file("arduinos.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream in(&file);
    bool foundArduino = false;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line.startsWith(arduinoId + ";"))
        {
            foundArduino = true;
            break;
        }
    }
    if (!foundArduino)
    {
        QTextStream out(&file);
        arduinosId->insert(arduinoId);
        out << arduinoId << ";" << bullBirthDate << ";" << "\n";
    }
    file.close();
}

// вытаскиваем инфу датчиков опредленного ардуино за какое-то время для пакета PacketID_GET_FULL_INFO
QString Server::processSensorsLog(QString &arduinoId, QString &timeLimit)
{
    QFile file("sensor_log.txt");

    int oneDayInSec = -3600 * 24;
    QDateTime now = QDateTime::currentDateTime();
    QDateTime dateTime;
    if (timeLimit == "За час")
    {
        dateTime = now.addSecs(-3600);
    }
    else if (timeLimit == "За сутки")
    {
        dateTime = now.addSecs(oneDayInSec);
    }
    else if (timeLimit == "За неделю")
    {
        dateTime = now.addSecs(oneDayInSec * 7);
    }
    else if (timeLimit == "За месяц")
    {
        dateTime = now.addSecs(oneDayInSec * 30);
    }
    else
    {
        dateTime = now.addSecs(oneDayInSec * 999);
    }
    QList<QPair<qint64, QString>> tempValues;
    QDateTime lieStart;
    qint64 totalLieSeconds = 0;
    qint64 maxLieSeconds = 0;
    bool isLying = false;
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList parts = line.split(';');
        if(parts.length() < 3)
        {
            continue;
        }
        QDateTime timestamp = QDateTime::fromString(parts[0], Qt::ISODate);
        QString id = parts[1];
        QString type = parts[2];
        QString value = parts[3];
        if (id == arduinoId && timestamp >= dateTime)
        {
            qint64 mSecsSinceEpoch = timestamp.toMSecsSinceEpoch();
            if (type == "temp")
            {
                tempValues.append({mSecsSinceEpoch, value});
            }
            else if (type == "obstacle")
            {
                int state = parts[3].toInt();
                if (state == 1 && !isLying)
                {
                    lieStart = timestamp;
                    isLying = true;
                }
                else if (state == 0 && isLying)
                {
                    qint64 secs = lieStart.secsTo(timestamp);
                    maxLieSeconds = std::max(secs, maxLieSeconds);
                    totalLieSeconds += secs;
                    isLying = false;
                }
            }
        }
    }
    file.close();
    if (isLying && isArduinoOnline(arduinoId))
    {
        totalLieSeconds += lieStart.secsTo(QDateTime::currentDateTime());
    }
    int len = tempValues.size();
    QString lieTimeText = QString::number(totalLieSeconds / 3600.0, 'g', 1) + "ч.";
    QString maxLieTimeText = QString::number(maxLieSeconds / 3600.0, 'g', 1) + "ч.";
    QString result =
        arduinoId + ";" + lieTimeText + ";" + maxLieTimeText + ";" + timeLimit + ";" + QString::number(len) + ";";
    for (int i = tempValues.size() - len; i < tempValues.size(); ++i)
    {
        result += QString::number(tempValues[i].first) + ';' + tempValues[i].second + ';';
    }
    return result;
}

// обновить запись заметки
void Server::updateArduinoNote(QString &arduinoId, QString &newNote)
{
    QFile file("arduinos.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QStringList lines;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList parts = line.split(';');
        if (parts.size() >= 3 && parts[0] == arduinoId)
        {
            parts[2] = newNote;
            lines.append(parts.join(';'));
        }
        else
        {
            lines.append(line);
        }
    }
    file.close();
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    QTextStream out(&file);
    for (QString &line : lines)
    {
        out << line << "\n";
    }
    file.close();
}

bool Server::isArduinoOnline(QString arduinoId)
{
    for (auto it = buffers.keyValueBegin(); it != buffers.keyValueEnd(); ++it)
    {
        QTcpSocket *socket = it->first;
        if (socket->objectName() == arduinoId)
        {
            return true;
        }
    }
    return false;
}

// сокет отсоединлся
void Server::onDisconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    removeSocket(socket);
}

// ошибка с сокетом
void Server::onError()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    removeSocket(socket);
}

void Server::onTimeout()
{
    // qInfo("TIMEOUT");
    auto *timer = qobject_cast<QTimer *>(sender());
    if (!timer)
    {
        return;
    }
    QTcpSocket *targetSocket = nullptr;
    for (auto it = clientTimers.begin(); it != clientTimers.end(); ++it)
    {
        if (it.value() == timer)
        {
            targetSocket = it.key();
            break;
        }
    }
    if (targetSocket != nullptr)
    {
        targetSocket->disconnectFromHost();
    }
}

void Server::removeSocket(QTcpSocket *socket)
{
    if (socket == nullptr || !buffers.contains(socket))
    {
        return;
    }
    if (socket->objectName() != "Qtapp")
    {
        broadcastToApps(PacketID_UPDATE_ROW_CELL_VALUE, socket->objectName() + ";Статус;Оффлайн");
    }
    qInfo() << "Client disconnected:" << socket->peerAddress().toString() << " " << socket->objectName();
    buffers.remove(socket);
    clientTimers[socket]->stop();
    clientTimers[socket]->deleteLater();
    clientTimers.remove(socket);
    socket->deleteLater();
}
