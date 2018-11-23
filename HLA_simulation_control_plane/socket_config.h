#ifndef SOCKET_CONFIG_H
#define SOCKET_CONFIG_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>


class SocketConfig :public QMainWindow
{
public:
    bool initSocket();
    void sendData(QString sendData);
    QTcpServer *myTCPServer;
    QTcpSocket *myTCPSocket;
    bool serverNewConnection();
    void serverDisConnection();
    bool receiveData();

    char buffer[1024];
    int bufferIdx;




};



#endif // SOCKET_CONFIG_H
