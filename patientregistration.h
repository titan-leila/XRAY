#ifndef PATIENTREGISTRATION_H
#define PATIENTREGISTRATION_H

#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QDebug>
#include "login.h"
#include <QKeyEvent>


namespace Ui {
class patientRegistration;
}

class patientRegistration : public QDialog
{
    Q_OBJECT
public:

    QSqlDatabase db;
    QString PATIENTID,fname, middle, lname, suffix, dob, gender, physician, description, anatomy, datetime, accession, prefix;

    QString retrieve(){ return PATIENTID; }
    void connClose(){

        db.close();
        db.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connOpen(){

            QString dbName( "/Users/leila/Downloads/newestXray/myDatabase.db" );
            db = QSqlDatabase::addDatabase( "QSQLITE" );
            qDebug() << dbName;
            db.setDatabaseName( dbName );
            db.open();
            if(!db.open()) { qDebug() << " Its didnt open";
                return false;
                 }
            else  return true;
    }

public:
    explicit patientRegistration(QWidget *parent = 0);
    ~patientRegistration();

private slots:

    void on_pushButton_saved_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_Imaging_clicked();

private:
    Ui::patientRegistration *ui;
    logIn *login;
    void keyPressEvent(QKeyEvent *event);


};

#endif // PATIENTREGISTRATION_H
