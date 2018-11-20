#include "socket_config.h"
#include "data_parse.h"

#define PORT_NUM  5550

//socket服务器初始化
int SocketConfig::initSocket()
{
    myTCPServer = new QTcpServer();
    int port = PORT_NUM;
    if(!myTCPServer->listen(QHostAddress::Any, port))
    {
        //QMessageBox::information(this, "QT通信网络", "服务器端监听失败");
        return 0;
    }
    else
    {
        connect(myTCPServer, SIGNAL(newConnection()), this, SLOT(serverNewConnection()));

        return 1;
        //QMessageBox::information(this, "QT通信网络", "服务器端监听成功");
    }
}

//建立连接
void SocketConfig::serverNewConnection()
{
    myTCPSocket = myTCPServer->nextPendingConnection();

    if(!myTCPSocket)
    {
        return;
    }
    else
    {
        connect(myTCPSocket, SIGNAL(readyRead()), this, SLOT(receiveData()));
        connect(myTCPSocket, SIGNAL(disconnected()), this, SLOT(serverDisConnection()));
    }
}

//服务器接收数据
void SocketConfig::receiveData()
{
    char buffer[1024] = {0};
    myTCPSocket->read(buffer,1024);
    if(strlen(buffer) > 0)
    {
        for(int i = 0; i < strlen(buffer); i++)
        {
            if(i < BUFFER_VAL_MAX)
            {
                parser.frameBuffers[parser.addIdx].buff[i] = buffer[i];
            }
            else
            {
                break;
            }
        }

        if(parser.addIdx < FRAME_NUM_MAX - 1)
        {
            parser.addIdx++;
        }
        else
        {
             parser.addIdx = 0;
        }
    }
    else
    {

    }
}
