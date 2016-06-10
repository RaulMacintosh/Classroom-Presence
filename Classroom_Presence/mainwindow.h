#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cstdio>       //printf
#include <cstring>      //memset
#include <cstdlib>      //exit
#include <netinet/in.h> //htons
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h> //socket
#include <unistd.h>     //close
#include <thread>
#include <iostream>
#include <vector>
#include <QTimer>
#include <QtGui>
#include <QCheckBox>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_connect_clicked();
    void server(const char *ip);
    void socketHandler(int socketDescriptor);
    void on_create_clicked();
    int doPresence();

    void on_save_clicked();

private:
    bool endOfMsg;
    string rfid;
    Ui::MainWindow *ui;
    std::thread serverThread;
    vector<string> studentsTags;
};

#endif // MAINWINDOW_H
