#include "creationwindow.h"
#include "ui_creationwindow.h"

CreationWindow::CreationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreationWindow){
    ui->setupUi(this);
}

CreationWindow::~CreationWindow(){
    delete ui;
}

void CreationWindow::passTagId(string *rfidPassed){
    rfid = rfidPassed;
}

void CreationWindow::on_createClass_clicked(){
    string auxPath = "mkdir ~/Desktop/IMD/";
    const char *path = auxPath.c_str();
    system(path);

    auxPath = "mkdir ~/Desktop/IMD/" + ui->discipline->text().toStdString();
    path = auxPath.c_str();
    system(path);

    auxPath = "mkdir ~/Desktop/IMD/" + ui->discipline->text().toStdString() + "/" + ui->classId->text().toStdString();
    path = auxPath.c_str();
    system(path);

    string auxFile = "touch ~/Desktop/IMD/" + ui->discipline->text().toStdString() + "/"
            + ui->classId->text().toStdString() + "/Turma.txt";
    const char *file = auxFile.c_str();
    system(file);
}

void CreationWindow::on_createStudent_clicked(){
    string auxRFID = *rfid;
    string auxPath = "echo \"" + ui->studentName->text().toStdString() + "|" + ui->studentId->text().toStdString() + "|"
            + auxRFID + "|\" >> ~/Desktop/IMD/" + ui->disciplineStudent->text().toStdString() + "/"
            + ui->classIdStudent->text().toStdString() + "/Turma.txt";

    const char *path = auxPath.c_str();

    system(path);

    auxPath = "sort ~/Desktop/IMD/" + ui->disciplineStudent->text().toStdString() + "/"
            + ui->classIdStudent->text().toStdString() + "/Turma.txt";

    path = auxPath.c_str();

    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(path, "r");
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
    int i;
    for(i = 0; result[i] == '\n' ; i++);
    result = result.substr(i,result.size());

    auxPath = "echo \"" + result + "\" > ~/Desktop/IMD/" + ui->disciplineStudent->text().toStdString() + "/"
            + ui->classIdStudent->text().toStdString() + "/Turma.txt";

    path = auxPath.c_str();

    system(path);
}

void CreationWindow::on_readTag_clicked(){
    ui->tagId->setText(QString::fromStdString(*rfid));
}
