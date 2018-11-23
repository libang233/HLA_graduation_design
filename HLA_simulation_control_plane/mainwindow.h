#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "socket_config.h"
#include "data_parse.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
   // void sysInit();
    void winSystemInit();
    void winMsgSend();
    void winMsgRead();
    void winNewConnect();

    void accept(QString msg);

private:
    Ui::MainWindow *ui;
    SocketConfig socketServer;
    ParserDef parser;
};

#endif // MAINWINDOW_H
