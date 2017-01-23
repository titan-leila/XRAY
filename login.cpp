#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

logIn::logIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logIn)
{
    ui->setupUi(this);
}

logIn::~logIn()
{
    delete ui;
}

void logIn::on_pushButton_clicked()
{
    QString password = ui->lineEdit_password->text();

    if (password == "deeznuts"){
        hide();
        settings = new Settings;
        settings->showFullScreen();
    }
    else QMessageBox::warning(this,"Login","Password incorrect");
}
