#include "tcpcilents.h"
#include<QDebug>

TcpCilents::TcpCilents(QObject *parent)
    : QObject(parent)
{
    socket = new QTcpSocket(this);

    connect(socket, &QTcpSocket::connected, this, &TcpCilents::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &TcpCilents::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &TcpCilents::onDisconnected);
    connect(socket, &QTcpSocket::errorOccurred, this, &TcpCilents::onError);
}

void TcpCilents::connectToCamera(const QString &ip, quint16 port)
{
    qDebug() << "Connecting to" << ip << port;
    socket->connectToHost(ip, port);
    // socket->abort();  // Important reset
    // socket->connectToHost(ip, port, QIODevice::ReadWrite);
}

void TcpCilents::onConnected()
{
    qDebug() << "Connected to Camera!";

}

void TcpCilents::onReadyRead()
{
    QByteArray data = socket->readAll();
    QString ascii = QString::fromUtf8(data);
    QString hex   = data.toHex(' ');

    emit dataReceived(ascii, hex);
}

void TcpCilents::onDisconnected()
{
qDebug() << "Camera disconnected!";
}

void TcpCilents::onError(QAbstractSocket::SocketError)
{
 qDebug() << "Error:" << socket->errorString();
}
