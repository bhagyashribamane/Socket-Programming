#include "TcpCilent.h"
#include <QDebug>

TcpClient::TcpClient(QObject *parent)
    : QObject(parent)
{
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

void TcpClient::connectToCamera(const QString &ip, quint16 port)
{
    lastIP = ip;
    lastPort = port;

    qDebug() << "Connecting to:" << ip << port;
    socket->abort();
    socket->connectToHost(ip, port);
}

void TcpClient::disconnectCamera()
{
    reconnectTimer.stop();
    socket->disconnectFromHost();
}

bool TcpClient::isConnected() const
{
    return socket->state() == QAbstractSocket::ConnectedState;
}

void TcpClient::onConnected()
{
    reconnectTimer.stop();
    emit connected();
}

void TcpClient::onReadyRead()
{
    QByteArray data = socket->readAll();
    QString ascii = QString::fromUtf8(data);
    QString hex = data.toHex(' ').toUpper();

    emit dataReceived(ascii, hex);
}

void TcpClient::onDisconnected()
{
    emit disconnected();
    reconnectTimer.start();
}

void TcpClient::onSocketError(QAbstractSocket::SocketError)
{
    emit errorOccurred(socket->errorString());

    if(!reconnectTimer.isActive())
    {
        reconnectTimer.start();
    }
}

void TcpClient::attemptReconnect()
{
    if(lastIP.isEmpty() || lastPort == 0)
        return;

    socket->abort();
    socket->connectToHost(lastIP, lastPort);
}
