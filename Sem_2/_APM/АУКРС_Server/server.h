#ifndef SERVER_H
#define SERVER_H

#include <QMap>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

class Server : public QObject
{
    Q_OBJECT
  public:
    explicit Server(QObject *parent = nullptr);
    void start();

  private slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();
    void onError();
    void onTimeout();
    void pingAllSockets();

  private:
    QTcpServer *tcpServer;
    QMap<QTcpSocket *, QByteArray> buffers;
    QMap<QTcpSocket *, QTimer *> clientTimers;
    QSet<QString> *arduinosId;
    void loadArduinosId();
    void setupPinger();
    void processBuffer(QTcpSocket *socket);
    void sendPacketTo(QTcpSocket *socket, qint8 id, const QString &data = "");
    void broadcastToApps(qint8 id, const QString &data);
    void handlePacket(QTcpSocket *socket, qint8 id, QStringList args);
    void checkAndAddArduino(QString &arduinoId, QString &bullBirthDate);
    QString processSensorsLog(QString &arduinoId, QString &timeLimit);
    void updateArduinoNote(QString &arduinoId, QString &newNote);
    bool isArduinoOnline(QString arduinoId);
    void removeSocket(QTcpSocket *socket);
};

#endif // SERVER_H
