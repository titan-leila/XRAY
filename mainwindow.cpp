#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // QPixmap pix("C:/Users/admin/Desktop/images/titan1.png");
   // ui->label_picture->setPixmap(pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBox_12_clicked()

{

    hide();
    menuPage = new mainMenu;
    menuPage->showFullScreen();

}
