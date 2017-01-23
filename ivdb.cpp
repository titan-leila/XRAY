#include "ivdb.h"
#include "ui_ivdb.h"
#include "images.h"
#include "patientdatabase.h"
#include "mainwindow.h"

IVDB::IVDB(QString x,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IVDB)
{
    ui->setupUi(this);
    QString patientid = x;
    qDebug() << patientid;
    QSqlQueryModel *modal = new QSqlQueryModel();
    registration.connOpen();

    QSqlQuery *qry = new QSqlQuery(registration.db);
    qry->prepare("select * from imageTable where PatientId = '"+patientid+"'");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_images->setModel(modal);
    registration.connClose();

}

IVDB::~IVDB()
{
    delete ui;
}

void IVDB::on_tableView_images_activated(const QModelIndex &index)
{
   Q_UNUSED(index);
}


void IVDB::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_S && Qt::Key_Control){
        login = new logIn;
        login->show();
    }
    if (event->key() == Qt::Key_Escape){
        close();
    }
}
