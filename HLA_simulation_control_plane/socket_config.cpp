#include "socket_config.h"
#include "data_parse.h"


#define PORT_NUM  5550



//socket服务器初始化
bool SocketConfig::initSocket()
{
    myTCPServer = new QTcpServer();
    int port = PORT_NUM;
    if(!myTCPServer->listen(QHostAddress::Any, port))
    {
        return false;
    }
    else
    {
        return true;
    }
}

//建立连接
bool SocketConfig::serverNewConnection()
{
    myTCPSocket = myTCPServer->nextPendingConnection();

    if(!myTCPSocket)
    {
        return false;
    }
    else
    {

        return true;
    }
}

//服务器接收数据
bool SocketConfig::receiveData()
{
    bufferIdx = 0;
    memset(&buffer, 0, sizeof(buffer));
    myTCPSocket->read(buffer,1024);
    bufferIdx = strlen(buffer);
    if(bufferIdx > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void SocketConfig::sendData(QString sendData)
{
    char sendMsgChar[1024] = {0};

    strcpy_s(sendMsgChar, sendData.toStdString().c_str());

    if(myTCPSocket->isValid())
    {
        int sendRe = myTCPSocket->write(sendMsgChar, strlen(sendMsgChar));
        if(-1 == sendRe)
        {
            //QMessageBox::information(this, "QT网络通信", "服务端发送数据失败！");
        }
    }
    else
    {
        //QMessageBox::information(this, "QT网络通信", "套接字无效！");
    }
}
