#ifndef SOCKET_CONFIG_H
#define SOCKET_CONFIG_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>


class SocketConfig  :public QMainWindow
{
public:
    int  initSocket();
    void sendData();

private slots:
    void serverNewConnection();
    void serverDisConnection();
    void receiveData();

private:
    QTcpServer *myTCPServer;
    QTcpSocket *myTCPSocket;

};

#endif // SOCKET_CONFIG_H
