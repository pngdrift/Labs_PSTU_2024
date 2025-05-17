#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QTcpSocket>

class Network : public QObject
{
    Q_OBJECT
  public:
    explicit Network(QObject *parent = nullptr);
    void connectToServer(QString &ip, quint16 port);

  public slots:
    void onDataSocket();
    void discardSocket();
    void displayError(QAbstractSocket::SocketError socketError);
    void handlePacket(qint8 id, QStringList args);
    void sendPacket(qint8 id, const QString &data = "");

  signals:
    void badConnection();
    void packetRecv(qint8 packetId, QStringList args);

  private:
    QTcpSocket *socket;
};

#endif // NETWORK_H
