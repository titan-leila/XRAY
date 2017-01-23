#include "secondxrayview.h"
#include "ui_secondxrayview.h"
#include "mainmenu.h"
#include "imagingsettings.h"
#include <QtSql>
#include <QMediaService>
#include <QMediaRecorder>
#include <QCameraViewfinder>
#include <QCameraInfo>
#include <QMediaMetaData>
#include <QCameraImageCapture>
#include <QShortcut>
#include <QVector>
#include <QMessageBox>
#include <QPalette>
#include <QCameraFocus>
#include <QtWidgets>


secondxrayview::secondxrayview(QString x,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secondxrayview),
    camera(0),
    imageCapture(0),
    mediaRecorder(0)
{
    ui->setupUi(this);
    patientid1 = x;
    setCamera(QCameraInfo::defaultCamera());


    if(patientid1 != ""){
        pRegister.connOpen();
        QSqlQuery query = QSqlQuery(pRegister.db);
        if( !query.exec( "SELECT Image from imageTable where PatientId = '"+patientid1+"' order by ImageId DESC limit 3"))
            qDebug() << "Error getting image from table:\n" << query.lastError();
        if(query.next()){
         outByteArray = query.value(0).toByteArray();
         outPixmap.loadFromData( outByteArray );
           }

        pRegister.connClose();
        ui->label_first->setPixmap(outPixmap);
       }

}

secondxrayview::~secondxrayview()
{
    delete ui;
    delete mediaRecorder;
    delete imageCapture;
    delete camera;


}

void secondxrayview::setCamera(const QCameraInfo &cameraInfo)
{
    delete mediaRecorder;
    delete imageCapture;
    delete camera;

    camera = new QCamera(cameraInfo);
    mediaRecorder = new QMediaRecorder(camera);
    imageCapture = new QCameraImageCapture(camera);
    camera->setViewfinder(ui->viewfinder);

    connect(imageCapture, SIGNAL(readyForCaptureChanged(bool)), this, SLOT(readyForCapture(bool)));
    connect(imageCapture, SIGNAL(imageCaptured(int,QImage)), this, SLOT(processCapturedImage(int,QImage)));

    camera->start();

}

void secondxrayview::on_pushButton_home_clicked()
{
    camera->stop();
    hide();
    mainMenu *x =new mainMenu;
    x->showFullScreen();

}


void secondxrayview::processCapturedImage(int requestId, const QImage &img)
{
    Q_UNUSED(requestId);
    pRegister.connOpen();
    QSqlQuery query = QSqlQuery(pRegister.db);
    QByteArray inByteArray, outByteArray;

    int w=ui->label_first->width();
    int h=ui->label_first->height();
    QImage scaledImage = img.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation);

    QBuffer inbuffer(&inByteArray);
    inbuffer.open(QIODevice::WriteOnly);
    scaledImage.save(&inbuffer,"PNG");

    QPixmap outPixmap = QPixmap();

    if(patientid1 == ""){
        if(!query.exec("insert into patientTable (Prefix,FirstName,Middle,LastName,Suffix,DateOfBirth,Gender,Physician,Description,Anatomy,Accession,DateTime) values ('','','','','','','','','','','','')"))
           QMessageBox::critical(this,tr("Patient Database"),query.lastError().text());
        if(!query.exec("select PatientId,LastName from patientTable order by PatientId desc limit 1"))
           QMessageBox::critical(this,tr("Patient Database"),query.lastError().text());
        if(query.next()){
         patientid1 = query.value(0).toString();
         lname = query.value(1).toString();
           }
        query.prepare("INSERT INTO imageTable (PatientId,LastName,Image) VALUES('"+patientid1+"','"+lname+"',:imageData)");
        query.bindValue(":imageData", inByteArray);
        if( !query.exec() )
            qDebug() << "Error inserting Image into table:\n" << query.lastError();
        if( !query.exec( "SELECT Image from imageTable where PatientId = '"+patientid1+"' order by ImageId DESC limit 3"))
            qDebug() << "Error getting image from table:\n" << query.lastError();
        if(query.next()){
         outByteArray = query.value(0).toByteArray();
         outPixmap.loadFromData( outByteArray );
           }
    }
  else {
    query.prepare("select LastName from patientTable where PatientId = '"+patientid1+"'");
    if (query.exec()){
        while(query.next()){
           lname = query.value(0).toString();
        }
    }
    query.prepare("INSERT INTO imageTable (PatientId,LastName,Image) VALUES('"+patientid1+"','"+lname+"',:imageData)");
    query.bindValue(":imageData", inByteArray);
    if( !query.exec() )
        qDebug() << "Error inserting Image into table:\n" << query.lastError();
    if( !query.exec( "SELECT Image from imageTable where PatientId = '"+patientid1+"' order by ImageId DESC limit 3"))
        qDebug() << "Error getting image from table:\n" << query.lastError();

    if(query.next()){
     outByteArray = query.value(0).toByteArray();
     outPixmap.loadFromData( outByteArray );
    }
}

    pRegister.connClose();
    ui->label_first->setPixmap(outPixmap);
}


void secondxrayview::on_pushButton_takePicture_clicked()
{

    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->searchAndLock();
    imageCapture->capture();
    camera->unlock();

}

void secondxrayview::on_pushButton_original_clicked()
{
    camera->stop();
    delete mediaRecorder;
    delete imageCapture;
    delete camera;

    hide();
    xrayImaging *x = new xrayImaging(patientid1);
    x->showFullScreen();

}


void secondxrayview::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_S && Qt::Key_Control){
        login = new logIn;
        login->show();
    }
    if (event->key() == Qt::Key_Escape){
        camera->stop();
        delete mediaRecorder;
        delete imageCapture;
        delete camera;
        close();
    }
}

void secondxrayview::on_pushButton_settings_clicked()
{
    imagingSettings *settings = new imagingSettings(camera,imageProcessing);
    settings->show();
}
