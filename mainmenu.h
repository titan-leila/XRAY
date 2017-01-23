#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include <QKeyEvent>
#include "patientdatabase.h"
#include "patientregistration.h"
#include "xrayimaging.h"
#include "hyperion.h"
#include "imageviddatabase.h"
#include "login.h"

namespace Ui {
class mainMenu;
}

class mainMenu : public QDialog
{
    Q_OBJECT

public:
    explicit mainMenu(QWidget *parent = 0);
    ~mainMenu();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::mainMenu *ui;
    patientDatabase *databasePage;
    patientRegistration *registrationPage;
    xrayImaging *xrayPage;
    hyperion *hyperionPage;
    ImageVidDatabase *imageVidPage;
    logIn *login;
    void keyPressEvent(QKeyEvent *event);


};

#endif // MAINMENU_H
