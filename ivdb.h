#ifndef IVDB_H
#define IVDB_H
#include "patientregistration.h"

#include <QDialog>
#include <QMessageBox>
#include <QKeyEvent>
#include "login.h"

namespace Ui {
class IVDB;
}

class IVDB : public QDialog
{
    Q_OBJECT

public:
    QString newPatient;
    explicit IVDB(QString x,QWidget *parent = 0);
    ~IVDB();

private slots:
    void on_tableView_images_activated(const QModelIndex &index);

private:
    Ui::IVDB *ui;
    patientRegistration registration;
    void keyPressEvent(QKeyEvent *event);
    logIn *login;
};

#endif // IVDB_H
