#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "creationwindow.h"
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>

#define MAXMSG 1024
#define MAXNAME 100
#define PORTNUM 4325

int MainWindow::doPresence(){
    int i;
    for(i = 0; i < studentsTags.size(); i++){
        if(studentsTags[i] == rfid){
            break;
        }
    }

    if(i == studentsTags.size()){
        return 0;
    }

    QTableWidgetItem *idColor = ui->presenceList->item(i,0);
    idColor->setTextColor(Qt::green);

    QTableWidgetItem *nameColor = ui->presenceList->item(i,1);
    nameColor->setTextColor(Qt::green);

    QTableWidgetItem *cBox = ui->presenceList->item(i,2);
    cBox->setCheckState(Qt::Checked);
    return 1;
}

void MainWindow::socketHandler(int socketDescriptor){
    int bytesReaded;
    string msg;

    if (socketDescriptor == -1){
        printf("[ERROR] Accept execution\n");
        exit(EXIT_FAILURE);
    }

    //receber uma msg do cliente
    bytesReaded = recv(socketDescriptor,&msg,sizeof(msg),0);

    if(endOfMsg){
        int i;
        for(i = 0; msg[i] > 40; i++);
        rfid += msg.substr(0, i);
        endOfMsg = false;
        doPresence();
    }else{
        int i;
        for(i = 0; msg[i] > 40; i++);
        rfid = msg.substr(0, i);
        endOfMsg = true;
    }

    if (bytesReaded == -1){
        printf("[ERRO] Receive execution\n");
        exit(EXIT_FAILURE);
    }else if (bytesReaded == 0){
        printf("Connection finished\n");
        exit(EXIT_SUCCESS);
    }

    ::close(socketDescriptor);
}

void MainWindow::server(const char *ip){
    struct sockaddr_in addr;
    int socketId;

    struct sockaddr_in addrClient;
    socklen_t addrClientSize = sizeof(struct sockaddr);
    int clientIdConnection;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORTNUM);
    //addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_addr.s_addr = inet_addr(ip);

    /*
     * Creating Socket
     *
     * PARAM1: AF_INET ou AF_INET6 (IPV4 ou IPV6)
     * PARAM2: SOCK_STREAM ou SOCK_DGRAM
     * PARAM3: protocolo (IP, UDP, TCP, etc).
    */
    socketId = socket(AF_INET, SOCK_STREAM, 0);

    if (socketId == -1){
        printf("[ERROR] Socket execution\n");
        exit(EXIT_FAILURE);
    }

    if ( ::bind(socketId, (struct sockaddr *)&addr, sizeof(struct sockaddr)) == -1 ){
        printf("[ERROR] Bind execution\n");
        exit(EXIT_FAILURE);
    }

    if ( listen( socketId, 10 ) == -1){
        printf("[ERROR] Listen execution\n");
        exit(EXIT_FAILURE);
    }

    while(1){
        printf("[LOG] Waiting for connections\n");
        clientIdConnection = accept( socketId,(struct sockaddr *) &addrClient,&addrClientSize );

        printf("Servidor: recebeu conexão de %s\n", inet_ntoa(addrClient.sin_addr));

        //disparar a thread
        std::thread t(&MainWindow::socketHandler, this, clientIdConnection);
        t.detach();
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    endOfMsg = false;
    QStringList titles;
    titles << "Matrícula" << "Nome" << "Presença";
    ui->presenceList->setColumnCount(3);
    ui->presenceList->setHorizontalHeaderLabels(titles);
}

MainWindow::~MainWindow(){
    delete ui;
    serverThread.detach();
}

void MainWindow::on_connect_clicked(){
    QString ip;

    char buffer[128];
    std::string result = "";
    FILE* pipe = popen("ifconfig en1 | grep inet", "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);

    int cont = 0;
    for(int i = 0; i < result.length(); i++){
        if(result[i] == '\n'){
            cont++;
        }

        if(cont == 2){
            ip = QString::fromStdString(result.substr((i+7),12));
            break;
        }
    }
    ui->serverIP->setText(ip);
    QByteArray ip_txt_array = ip.toLatin1();
    const char *ip_txt_chr = ip_txt_array.data();

    serverThread = std::thread(&MainWindow::server, this, ip_txt_chr);

    string auxPath = "cat ~/Desktop/IMD/" + ui->disCode->text().toStdString() + "/" + ui->classCode->text().toStdString()
            + "/Turma.txt";

    const char *path = auxPath.c_str();

    char buffer2[128];
    std::string result2 = "";
    FILE* pipe2 = popen(path, "r");
    if (!pipe2) throw std::runtime_error("popen() failed!");
    try {
        while (!feof(pipe2)) {
            if (fgets(buffer2, 128, pipe2) != NULL)
                result2 += buffer2;
        }
    } catch (...) {
        pclose(pipe2);
        throw;
    }
    pclose(pipe2);

    int tokenCounter = 0;
    int nameBegin = 0;
    int idBegin = 0;
    int tagBegin = 0;
    int row = 0;
    for(int i = 0; i < result2.size(); i++){
        if(result2[i] == '|'){
            if(tokenCounter == 0){
                ui->presenceList->insertRow(ui->presenceList->rowCount());
                ui->presenceList->setItem(ui->presenceList->rowCount()-1, 1,new QTableWidgetItem(QString::fromStdString(result2.substr(nameBegin, (i-nameBegin)))));
                QTableWidgetItem *nameColor = ui->presenceList->item(ui->presenceList->rowCount()-1,1);
                nameColor->setTextColor(Qt::red);

                QTableWidgetItem *cBox = new QTableWidgetItem();
                cBox->setCheckState(Qt::Unchecked);
                ui->presenceList->setItem(ui->presenceList->rowCount()-1, 2, cBox);
                idBegin = i+1;
                tokenCounter++;
            }else if(tokenCounter == 1){
                ui->presenceList->setItem(ui->presenceList->rowCount()-1, 0, new QTableWidgetItem(QString::fromStdString(result2.substr(idBegin, (i-idBegin)))));
                QTableWidgetItem *idColor = ui->presenceList->item(ui->presenceList->rowCount()-1,0);
                idColor->setTextColor(Qt::red);
                tagBegin = i+1;
                tokenCounter++;
            }else if(tokenCounter == 2){
                studentsTags.push_back(result2.substr(tagBegin, (i-tagBegin)));
                nameBegin = i+1;
                row++;
                tokenCounter = 0;
            }
        }
    }
}

void MainWindow::on_create_clicked(){
    CreationWindow w;
    w.setModal(true);
    w.passTagId(&rfid);
    w.exec();
}

void MainWindow::on_save_clicked(){
    string dateText = ui->date->text().toStdString();
    dateText = dateText.substr(0,2) + "-" + dateText.substr(3,2) + "-" + dateText.substr(6,2) + ".txt";

    for(int i = 0; i < studentsTags.size(); i++){
        if(ui->presenceList->item(i,2)->checkState() == Qt::Checked){
            string auxPath = "echo \"" + ui->presenceList->item(i,1)->text().toStdString() + " - "
                    + ui->presenceList->item(i,0)->text().toStdString() + "        PRESENÇA\" >> ~/Desktop/IMD/"
                    + ui->disCode->text().toStdString() + "/" + ui->classCode->text().toStdString() + "/"
                    + dateText;

            const char *path = auxPath.c_str();

            system(path);
        }else{
            string auxPath = "echo \"" + ui->presenceList->item(i,1)->text().toStdString() + " - "
                    + ui->presenceList->item(i,0)->text().toStdString() + "        FALTA\" >> ~/Desktop/IMD/"
                    + ui->disCode->text().toStdString() + "/" + ui->classCode->text().toStdString() + "/"
                    + dateText;

            const char *path = auxPath.c_str();

            system(path);
        }
    }
}
