#ifndef PATIENTDATABASE_H
#define PATIENTDATABASE_H

#include <QDialog>
#include "login.h"
#include <QKeyEvent>
#include "patientregistration.h"
#include "xrayimaging.h"

 //extern QString patientid1;

namespace Ui {
class patientDatabase;
}

class patientDatabase : public QDialog
{
    Q_OBJECT

public:
    QString patientid1;
    explicit patientDatabase(QWidget *parent = 0);
    ~patientDatabase();

private slots:

    void on_pushButton_2_clicked();

    void on_tableView_view_activated(const QModelIndex &index);

    void on_pushButton_edit_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_images_clicked();

private:
    Ui::patientDatabase *ui;
    patientRegistration patientR;
    xrayImaging *x;
    void keyPressEvent(QKeyEvent *event);
    logIn *login;

};

#endif // PATIENTDATABASE_H
