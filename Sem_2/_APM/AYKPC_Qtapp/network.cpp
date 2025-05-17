#include "network.h"
#include "packetids.h"
#include <QMessageBox>

Network::Network(QObject *parent) : QObject{parent}
{
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &Network::onDataSocket);
    connect(socket, &QTcpSocket::disconnected, this, &Network::discardSocket);
    connect(socket, &QAbstractSocket::errorOccurred, this, &Network::displayError);
}

// подключение к серверу по адресу и порту
void Network::connectToServer(QString &host, quint16 port)
{
    socket->connectToHost(host, port);
    if (socket->waitForConnected(2000))
    {
        sendPacket(PacketID_HELLO, "IAMQTAPP");
    }
    else
    {
        emit badConnection();
    }
}

// новые данные доступны
void Network::onDataSocket()
{
    QByteArray buffer = socket->readAll();
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
        handlePacket(id, str.split(";"));
        buffer = buffer.mid(len);
    }
}

// отправка пакета серверу
void Network::sendPacket(qint8 id, const QString &data)
{
    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);
    qint32 len = data.toUtf8().size() + PacketHeaderSize;
    out << len;
    out << id;
    packet.append(data.toUtf8());
    socket->write(packet);
}

// обработка пакета пинга или вызов сигнала
void Network::handlePacket(qint8 id, QStringList args)
{
    if (id == PacketID_PING)
    {
        sendPacket(PacketID_PONG);
    }
    else
    {
        emit packetRecv(id, args);
    }
}

// сокет вышел
void Network::discardSocket()
{
    socket->deleteLater();
    socket = nullptr;
    qInfo("Disconnected");
}

// ошибка сокета
void Network::displayError(QAbstractSocket::SocketError socketError)
{
    // qInfo(socketError);
}
