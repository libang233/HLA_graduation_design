#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    connect(ui->initBtn, SIGNAL(clicked()), this, SLOT(winSystemInit()));
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(winMsgSend()));

    connect(&parser, SIGNAL(send(QString)), this, SLOT(accept(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::winSystemInit()
{


    if(socketServer.initSocket() == false)
    {
        QMessageBox::information(this, "QT通信网络", "服务器端监听失败");
    }
    else
    {
        connect(socketServer.myTCPServer, SIGNAL(newConnection()), this, SLOT(winNewConnect()));
        QMessageBox::information(this, "QT通信网络", "服务器端监听成功");

    }


    parser.start();
}

void MainWindow::accept(QString msg)
{
    QMessageBox::information(this, "QT通信网络", msg);
}

void MainWindow::winNewConnect()
{
    if(socketServer.serverNewConnection() == true)
    {
        QMessageBox::information(this, "QT网络通信", "成功接收客户端连接");
        connect(socketServer.myTCPSocket, SIGNAL(readyRead()), this, SLOT(winMsgRead()));
        //connect(socketServer.myTCPSocket, SIGNAL(disconnected()), this, SLOT(serverDisConnection()));
    }
    else
    {
        QMessageBox::information(this, "QT网络通信", "未能正确获取客户端连接");
    }
}

void MainWindow::winMsgRead()
{
    socketServer.receiveData();

    //QMessageBox::information(this, "QT网络通信", QString("%1").arg(socketServer.bufferIdx));

    for(int i = 0; i < socketServer.bufferIdx; i++)
    {
        if(parser.socketBuffer.addIdx >= SOCKET_BUFF_VAL_MAX)
        {
           parser.socketBuffer.addIdx = 0;
        }

        parser.socketBuffer.buff[parser.socketBuffer.addIdx++] = socketServer.buffer[i];
    }

    /*
    for(int i = 0; i < socketServer.bufferIdx; i++)
    {
        if(i < BUFFER_VAL_MAX)
        {
            parser.frameBuffers[parser.addIdx].buff[i] = socketServer.buffer[i];
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
    */
}

void MainWindow::winMsgSend()
{
    QString sendMsg = ui->testForSend->toPlainText();

    socketServer.sendData(sendMsg);
}
