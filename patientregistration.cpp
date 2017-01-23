#include "patientregistration.h"
#include "ui_patientregistration.h"
#include <QMessageBox>
#include "mainmenu.h"
#include "xrayimaging.h"
#include <QSqlQuery>


patientRegistration::patientRegistration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::patientRegistration)
{
    ui->setupUi(this);
    QDate date = QDate::currentDate();
    ui->dateEdit_dob->setCalendarPopup(true);
    ui->dateEdit_dob->setDate(date);

    QDateTime datetime = QDateTime::currentDateTime();
    ui->dateTimeEdit->setCalendarPopup(true);
    ui->dateTimeEdit->setDateTime(datetime);

    ui->lineEdit_patientid->setValidator( new QDoubleValidator(0, 100, 2, this) );
    ui->lineEdit_accession->setValidator( new QDoubleValidator(0, 100, 2, this) );

    connOpen();
    QSqlQuery query = QSqlQuery( db );
/*
    query.exec("drop table patientTable");
    query.exec("drop table imageTable");
    query.exec("drop table videoTable");
*/
      query.exec( "CREATE TABLE IF NOT EXISTS patientTable (PatientId INTEGER PRIMARY KEY AUTOINCREMENT, Prefix varchar(15), FirstName varchar(30), Middle varchar(30), LastName varchar(30), Suffix varchar(15), DateOfBirth varchar(10), Gender varchar(20), Physician varchar(40), Description varchar(50), Anatomy varchar(20),  Accession varchar(16), Datetime varchar(20))");
      query.exec( "CREATE TABLE IF NOT EXISTS imageTable (ImageId INTEGER PRIMARY KEY AUTOINCREMENT, PatientId varchar(16) NOT NULL, LastName varchar(30) NOT NULL, Image blob NOT NULL, foreign key(PatientId) references patientTable(PatientId))");
      query.exec( "CREATE TABLE IF NOT EXISTS videoTable (VideoId INTEGER PRIMARY KEY AUTOINCREMENT, PatientId varchar(16) NOT NULL, LastName varchar(30) NOT NULL, Video blob NOT NULL, foreign key(PatientId) references patientTable(PatientId))");
      connClose();

}

patientRegistration::~patientRegistration()
{
    delete ui;
}


void patientRegistration::on_pushButton_saved_clicked()
{
    anatomy=ui->comboBox_anatomy->currentText();
    accession=ui->lineEdit_accession->text();
    fname=ui->lineEdit_first->text();
    middle=ui->lineEdit_middle->text();
    lname=ui->lineEdit_last->text();
    suffix=ui->lineEdit_suffix->text();
    prefix=ui->lineEdit_prefix->text();
    dob=ui->dateEdit_dob->text();
    gender=ui->comboBox_sex->currentText();
    PATIENTID = ui->lineEdit_patientid->text();
    physician=ui->lineEdit_physician->text();
    description=ui->lineEdit_description->text();
    datetime=ui->dateTimeEdit->text();
    connOpen();
    QSqlQuery qry;
    if(PATIENTID == ""){
    if(!qry.exec("insert into patientTable (Prefix,FirstName,Middle,LastName,Suffix,DateOfBirth,Gender,Physician,Description,Anatomy,Accession,DateTime) values ('"+prefix+"','"+fname+"','"+middle+"','"+lname+"','"+suffix+"','"+dob+"','"+gender+"','"+physician+"','"+description+"','"+anatomy+"','"+accession+"','"+datetime+"')"))
    QMessageBox::critical(this,tr("Patient Database"),qry.lastError().text());
    }
    else{
    if(!qry.exec("insert into patientTable (PatientId,Prefix,FirstName,Middle,LastName,Suffix,DateOfBirth,Gender,Physician,Description,Anatomy,Accession,DateTime) values ('"+PATIENTID+"','"+prefix+"','"+fname+"','"+middle+"','"+lname+"','"+suffix+"','"+dob+"','"+gender+"','"+physician+"','"+description+"','"+anatomy+"','"+accession+"','"+datetime+"')"))
    QMessageBox::critical(this,tr("Patient Database"),qry.lastError().text());
    }
    connClose();
}

void patientRegistration::on_pushButton_5_clicked()
{
    hide();
    mainMenu *x =new mainMenu;
    x->showFullScreen();
}

void patientRegistration::on_pushButton_Imaging_clicked()
{

    anatomy=ui->comboBox_anatomy->currentText();
    accession=ui->lineEdit_accession->text();
    fname=ui->lineEdit_first->text();
    middle=ui->lineEdit_middle->text();
    lname=ui->lineEdit_last->text();
    suffix=ui->lineEdit_suffix->text();
    prefix=ui->lineEdit_prefix->text();
    dob=ui->dateEdit_dob->text();
    gender=ui->comboBox_sex->currentText();
    PATIENTID = ui->lineEdit_patientid->text();
    physician=ui->lineEdit_physician->text();
    description=ui->lineEdit_description->text();
    datetime=ui->dateTimeEdit->text();

    connOpen();
    QSqlQuery qry;
    if(PATIENTID == "")
        qry.exec("insert into patientTable (Prefix,FirstName,Middle,LastName,Suffix,DateOfBirth,Gender,Physician,Description,Anatomy,Accession,DateTime) values ('"+prefix+"','"+fname+"','"+middle+"','"+lname+"','"+suffix+"','"+dob+"','"+gender+"','"+physician+"','"+description+"','"+anatomy+"','"+accession+"','"+datetime+"')");
    else
        qry.exec("insert into patientTable (PatientId,Prefix,FirstName,Middle,LastName,Suffix,DateOfBirth,Gender,Physician,Description,Anatomy,Accession,DateTime) values ('"+PATIENTID+"','"+prefix+"','"+fname+"','"+middle+"','"+lname+"','"+suffix+"','"+dob+"','"+gender+"','"+physician+"','"+description+"','"+anatomy+"','"+accession+"','"+datetime+"')");

    connClose();
    hide();
    xrayImaging *x = new xrayImaging(PATIENTID);
    x->showFullScreen();
}

void patientRegistration::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_S && Qt::Key_Control){
        login = new logIn;
        login->show();
    }
    if (event->key() == Qt::Key_Escape){
        close();
    }
}
