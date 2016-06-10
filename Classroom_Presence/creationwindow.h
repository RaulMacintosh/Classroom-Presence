#ifndef CREATIONWINDOW_H
#define CREATIONWINDOW_H

#include <QDialog>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

namespace Ui {
class CreationWindow;
}

class CreationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CreationWindow(QWidget *parent = 0);
    ~CreationWindow();
    void passTagId(string *rfidPassed);

private slots:
    void on_createClass_clicked();
    void on_createStudent_clicked();

    void on_readTag_clicked();

private:
    Ui::CreationWindow *ui;
    string *rfid;
};

#endif // CREATIONWINDOW_H
