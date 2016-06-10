#include "createwindow.h"
#include "ui_createwindow.h"

createwindow::createwindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::createwindow){
    ui->setupUi(this);
}

createwindow::~createwindow(){
    delete ui;
}
