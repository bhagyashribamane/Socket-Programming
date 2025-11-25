#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);

    void connectToCamera(const QString &ip, quint16 port);
    void disconnectCamera();
    bool isConnected() const;

signals:
    void connected();
    void disconnected();
    void dataReceived(QString asciiData, QString hexData);
    void errorOccurred(QString message);

private slots:
    void onConnected();
    void onReadyRead();
    void onDisconnected();
    void onSocketError(QAbstractSocket::SocketError socketError);
    void attemptReconnect();

private:
    QTcpSocket *socket;
    QTimer reconnectTimer;
    QString lastIP;
    quint16 lastPort;
};

#endif // TCPCLIENT_H
