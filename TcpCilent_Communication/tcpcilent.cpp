#include "TcpCilent.h"
#include <QDebug>

TcpClient::TcpClient(QObject *parent)
    : QObject(parent)
{
    // Creates a new TCP socket object that will be used to communicate with the camera or any TCP server.
    socket = new QTcpSocket(this);
    lastIP = "";
    lastPort = 0;

    connect(socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
    connect(socket, &QTcpSocket::errorOccurred, this, &TcpClient::onSocketError);

    reconnectTimer.setInterval(3000);
    reconnectTimer.setSingleShot(false);
    connect(&reconnectTimer, &QTimer::timeout, this, &TcpClient::attemptReconnect);
}

// This function is used to start a TCP connection to the camera using an IP address and port number.
void TcpClient::connectToCamera(const QString &ip, quint16 port)
{
    lastIP = ip;
    lastPort = port;

    qDebug() << "Connecting to:" << ip << port;
    // immediately stop any exisiting connection
    socket->abort();
    // Asks the QTcpSocket to connect to the given IP and port.
    socket->connectToHost(ip, port);
}
// This function is called when the user presses the Disconnect button or when the program
// wants to end the connection manually.
void TcpClient::disconnectCamera()
{
    reconnectTimer.stop();
    socket->disconnectFromHost();
}
// This function checks if the TCP socket is currently connected to the server/camera and then returns true or false
bool TcpClient::isConnected() const
{
    return socket->state() == QAbstractSocket::ConnectedState;
}

// This function is a slot and runs automatically when the socket successfully connects to the camera/device.
void TcpClient::onConnected()
{
    reconnectTimer.stop();
    emit connected();
}
// This function is a slot and runs automatically whenever the camera/device sends data.
void TcpClient::onReadyRead()
{
// Reads all incoming raw bytes from the TCP socket.Stores it in a QByteArray, which is used for binary data.
    QByteArray data = socket->readAll();
// Converts the raw bytes (data) into a human readable text string.
    QString ascii = QString::fromUtf8(data);
// Converts the same received bytes into hexadecimal format. ' ' adds a space between each byte for readability. .toUpper() makes hex letters uppercase.
    QString hex = data.toHex(' ').toUpper();

    emit dataReceived(ascii, hex);
}
// This function is automatically called when the TCP connection to the camera is lost.
void TcpClient::onDisconnected()
{
    emit disconnected();
    reconnectTimer.start();
}
// This function runs when something goes wrong with the TCP socket
void TcpClient::onSocketError(QAbstractSocket::SocketError)
{
    emit errorOccurred(socket->errorString());
// Before starting reconnect attempts, it checks if reconnect timer is already running.
    if(!reconnectTimer.isActive())
    {
        reconnectTimer.start();
    }
}
// This function is used to automatically reconnect to the camera when the connection is lost.
void TcpClient::attemptReconnect()
{
    if(lastIP.isEmpty() || lastPort == 0)
        return;

    socket->abort();
    socket->connectToHost(lastIP, lastPort);
}
