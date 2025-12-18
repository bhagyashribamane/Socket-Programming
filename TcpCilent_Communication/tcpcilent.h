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

    // this function is used for connect to the camera
    void connectToCamera(const QString &ip, quint16 port);
    // Disconnect  camera
    void disconnectCamera();
    //return  true if socket is connected
    bool isConnected() const;

signals:
    // This signal is emitted when TCP successfully connects to the camera.
    void connected();
    // This signal is emitted when connection is lost or intentionally closed.
    void disconnected();
    // This signal is emitted when data comes from the camera. in this function data received in two ways ascii or hex
    void dataReceived(QString asciiData, QString hexData);
    // This signal is emitted when a network error happens.
    void errorOccurred(QString message);

private slots:
    // This slot is called when the socket successfully connects.
    void onConnected();
    // This slot is triggered whenever new data arrives from the camera.
    void onReadyRead();
    // The camera disconnects
    void onDisconnected();
    // his slot runs when any socket error occurs,
    // QAbstractSocket::SocketError==>It's an enum type from Qt that represents different kinds of network errors.
    void onSocketError(QAbstractSocket::SocketError socketError);
    // This slot is connected to a timer.
    void attemptReconnect();

private:
    // This is the main network object used to connect, send,
    // and receive data from your camera/server.It represents the actual TCP communication link.
    QTcpSocket *socket;
    // This timer is used to automatically retry connection if the device disconnects or fails to connect.
    QTimer reconnectTimer;
    // This stores the last IP address used for connection.
    QString lastIP;
   // TCP port number stored as unsigned 16-bit integer.Same purpose as lastIP: used for reconnect attempts.
    quint16 lastPort;
};

#endif // TCPCLIENT_H
