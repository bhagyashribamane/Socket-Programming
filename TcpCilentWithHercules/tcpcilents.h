#ifndef TCPCILENTS_H
#define TCPCILENTS_H

#include <QObject>
#include<QTcpSocket>

class TcpCilents : public QObject
{
    Q_OBJECT
public:
    explicit TcpCilents(QObject *parent = nullptr);
    void connectToCamera(const QString &ip, quint16 port);

signals:
    void dataReceived(QString asciiData, QString hexData);

private slots:
    void onConnected();
    void onReadyRead();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError);

private:
    QTcpSocket *socket;
};
#endif // TCPCILENTS_H
