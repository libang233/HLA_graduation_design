#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "socket_config.h"

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
    void serverInit();
    void msgSend();
    void msgRead();
    void winNewConnect();

private:
    Ui::MainWindow *ui;
    SocketConfig socketServer;
};

#endif // MAINWINDOW_H
