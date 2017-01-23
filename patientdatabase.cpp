#include "patientdatabase.h"
#include "ui_patientdatabase.h"
#include "mainmenu.h"
#include "images.h"
#include <QMessageBox>


patientDatabase::patientDatabase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::patientDatabase)
{
    ui->setupUi(this);
    QSqlQueryModel *modal = new QSqlQueryModel();
    patientR.connOpen();

    QSqlQuery *qry = new QSqlQuery(patientR.db);
    qry->prepare("select * from patientTable");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_view->setModel(modal);
    patientR.connClose();
    ui->lineEdit_patientId->setReadOnly(true);
    ui->lineEdit_Accession->setReadOnly(true);
    QString patientid1;

}

patientDatabase::~patientDatabase()
{
    delete ui;
}


void patientDatabase::on_pushButton_2_clicked()
{
    hide();
    mainMenu *x =new mainMenu;
    x->showFullScreen();
}


void patientDatabase::on_tableView_view_activated(const QModelIndex &index)
{
     QString value = ui->tableView_view->model()->data(index).toString();
     patientR.connOpen();
     QSqlQuery qry;
    // qry.prepare("select * from patientTable where Prefix ='"+value+"' or FirstName ='"+value+"' or LastName ='"+value+"' or Middle ='"+value+"' or Suffix ='"+value+"' or DateOfBirth ='"+value+"' or Gender ='"+value+"' or Physician ='"+value+"' or Description ='"+value+"' or Anatomy ='"+value+"' or Accession ='"+value+"' or Datetime ='"+value+"'");

    if (qry.exec("select * from patientTable where PatientId ='"+value+"' or Prefix ='"+value+"' or FirstName ='"+value+"' or LastName ='"+value+"' or Middle ='"+value+"' or Suffix ='"+value+"' or DateOfBirth ='"+value+"' or Gender ='"+value+"' or Physician ='"+value+"' or Description ='"+value+"' or Anatomy ='"+value+"' or Accession ='"+value+"' or Datetime ='"+value+"'")){
        while(qry.next()){
           ui->lineEdit_patientId->setText(qry.value(0).toString());
           patientid1 = qry.value(0).toString();
           ui->lineEdit_prefix->setText(qry.value(1).toString());
           ui->lineEdit_first->setText(qry.value(2).toString());
           ui->lineEdit_middle->setText(qry.value(3).toString());
           ui->lineEdit_last->setText(qry.value(4).toString());
           ui->lineEdit_suffix->setText(qry.value(5).toString());
           ui->dateEdit_dob->setDate(qry.value(6).toDate());
           ui->comboBox_gender->setCurrentText(qry.value(7).toString());
           ui->lineEdit_physician->setText(qry.value(8).toString());
           ui->lineEdit_Description->setText(qry.value(9).toString());
           ui->comboBox_anatomy->setCurrentText(qry.value(10).toString());
           ui->lineEdit_Accession->setText(qry.value(11).toString());
           ui->dateTimeEdit->setDateTime(qry.value(12).toDateTime());
        }
    }
    else QMessageBox::critical(this,tr("Patient Database"),qry.lastError().text());

        Images *x = new Images(patientid1);
        x->showFullScreen();

    patientR.connClose();
}



void patientDatabase::on_pushButton_edit_clicked()
{
    QString fname, middle, lname, suffix, dob, gender, physician, description, anatomy, datetime,patientId,accession,prefix;
    anatomy=ui->comboBox_anatomy->currentText();
    accession=ui->lineEdit_Accession->text();
    fname=ui->lineEdit_first->text();
    middle=ui->lineEdit_middle->text();
    lname=ui->lineEdit_last->text();
    suffix=ui->lineEdit_suffix->text();
    prefix=ui->lineEdit_prefix->text();
    dob=ui->dateEdit_dob->text();
    gender=ui->comboBox_gender->currentText();
    patientId=ui->lineEdit_patientId->text();
    physician=ui->lineEdit_physician->text();
    description=ui->lineEdit_Description->text();
    datetime=ui->dateTimeEdit->text();
    patientR.connOpen();
    QSqlQuery qry;

    qry.prepare("update patientTable set PatientId='"+patientId+"',Prefix='"+prefix+"',FirstName='"+fname+"',Middle='"+middle+"',LastName='"+lname+"',Suffix='"+suffix+"',DateOfBirth='"+dob+"',Gender='"+gender+"',Physician='"+physician+"',Description='"+description+"',Anatomy='"+anatomy+"',Accession='"+accession+"',Datetime='"+datetime+"'where PatientId='"+patientId+"'");

    if (qry.exec()) {
        QSqlQueryModel *modal = new QSqlQueryModel();
        QSqlQuery *qry2 = new QSqlQuery(patientR.db);
        qry2->prepare("select * from patientTable");
        qry2->exec();
        modal->setQuery(*qry2);
        ui->tableView_view->setModel(modal);
        patientR.connClose();
    }
else QMessageBox::critical(this,tr("Patient Database"),qry.lastError().text());

}

void patientDatabase::on_pushButton_delete_clicked()
{
    QString patientId;
    patientId=ui->lineEdit_patientId->text();
    patientR.connOpen();
    QSqlQuery qry;
    qry.prepare("Delete from patientTable where PatientId='"+patientId+"'");

    if (qry.exec()) {
        QSqlQueryModel *modal = new QSqlQueryModel();
        QSqlQuery *qry2 = new QSqlQuery(patientR.db);
        qry2->prepare("select * from patientTable");
        qry2->exec();
        modal->setQuery(*qry2);
        ui->tableView_view->setModel(modal);
        patientR.connClose();

    }
else QMessageBox::critical(this,tr("Patient Database"),qry.lastError().text());

}


void patientDatabase::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_S && Qt::Key_Control){
        login = new logIn;
        login->show();
    }
    if (event->key() == Qt::Key_Escape){
        close();
    }
}

void patientDatabase::on_pushButton_images_clicked()
{
    hide();
    x = new xrayImaging(patientid1);
    x->showFullScreen();
}
