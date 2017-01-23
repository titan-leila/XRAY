#include "mainmenu.h"
#include "ui_mainmenu.h"

mainMenu::mainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainMenu)
{
    ui->setupUi(this);
  //  QPixmap pix("C:/Users/admin/Desktop/images/titan1.png");
 //   ui->label_picture->setPixmap(pix);
}

mainMenu::~mainMenu()
{
    delete ui;
}

void mainMenu::on_pushButton_2_clicked()  // start imaging
{
    //hide();
    xrayPage = new xrayImaging("");
    xrayPage->showFullScreen();
}

void mainMenu::on_pushButton_3_clicked()  // patient registration
{
   // hide();
    registrationPage = new patientRegistration;
    registrationPage->showFullScreen();
}

void mainMenu::on_pushButton_clicked()  // patient records
{
   // hide();
    databasePage = new patientDatabase;
    databasePage->showFullScreen();
}

void mainMenu::on_pushButton_4_clicked()  // hyperion
{
   // hide();
    hyperionPage = new hyperion;
    hyperionPage->showFullScreen();
}

void mainMenu::on_pushButton_5_clicked()
{
   // hide();
    imageVidPage = new ImageVidDatabase;
    imageVidPage->showFullScreen();

}

void mainMenu::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_S && Qt::Key_Control){
        login = new logIn;
        login->show();
    }
    if (event->key() == Qt::Key_Escape){
        close();
    }
}
