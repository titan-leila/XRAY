#include "xrayimaging.h"
#include "ui_xrayimaging.h"
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
#include <QCameraFocus>
#include <QDebug>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QtWidgets>


xrayImaging::xrayImaging(QString x,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::xrayImaging),
    camera(0),
    imageCapture(0),
    mediaRecorder(0),
    isCapturingImage(false),
    applicationExiting(false)
{
    patientid1 = x;
    ui->setupUi(this);
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
        if(query.next()){
        outByteArray= query.value(0).toByteArray();
        outPixmap2.loadFromData( outByteArray );
        }
        if(query.next()){
            outByteArray= query.value(0).toByteArray();
            outPixmap3.loadFromData( outByteArray );
        }
        pRegister.connClose();
        ui->label_first->setPixmap(outPixmap);
        ui->label_second->setPixmap(outPixmap2);
        ui->label_third->setPixmap(outPixmap3);
    }

}

xrayImaging::~xrayImaging()
{
    delete ui;
    delete mediaRecorder;
    delete imageCapture;
    delete camera;


}

void xrayImaging::setCamera(const QCameraInfo &cameraInfo)
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

void xrayImaging::on_pushButton_clicked()
{
    camera->stop();
    hide();
    mainMenu *x =new mainMenu;
    x->showFullScreen();
}

void xrayImaging::on_pushButton_2_clicked()
{
  imagingSettings *x = new imagingSettings(camera,imageProcessing);
  x->show();

}

void xrayImaging::processCapturedImage(int requestId, const QImage &img)
{
    Q_UNUSED(requestId);
    pRegister.connOpen();
    QSqlQuery query = QSqlQuery(pRegister.db);
    int w=ui->label_first->width();
    int h=ui->label_first->height();
    QImage scaledImage = img.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation);

    QBuffer inbuffer(&inByteArray);
    inbuffer.open(QIODevice::WriteOnly);
    scaledImage.save(&inbuffer,"PNG");

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
        if( !query.exec( "SELECT ImageId,Image from imageTable where PatientId = '"+patientid1+"' order by ImageId DESC limit 3"))
            qDebug() << "Error getting image from table:\n" << query.lastError();
        if(query.next()){
            imageidint=query.value(0).toInt();
            outByteArray = query.value(1).toByteArray();
            outPixmap.loadFromData(outByteArray);
              }
        if(query.next()){
            outByteArray= query.value(1).toByteArray();
         outPixmap2.loadFromData( outByteArray );
        }
        if(query.next()){
            outByteArray= query.value(1).toByteArray();
            outPixmap3.loadFromData( outByteArray );
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
    if( !query.exec( "SELECT ImageId,Image from imageTable where PatientId = '"+patientid1+"' order by ImageId DESC limit 3"))
        qDebug() << "Error getting image from table:\n" << query.lastError();

    if(query.next()){
        imageidint = query.value(0).toInt();
        outByteArray = query.value(1).toByteArray();
        outPixmap.loadFromData( outByteArray );
       }
    if(query.next()){
        outByteArray= query.value(1).toByteArray();
        outPixmap2.loadFromData( outByteArray );
    }
    if(query.next()){
        outByteArray= query.value(1).toByteArray();
        outPixmap3.loadFromData( outByteArray );
    }
}


    pRegister.connClose();
    ui->label_first->setPixmap(outPixmap);
    ui->label_second->setPixmap(outPixmap2);
    ui->label_third->setPixmap(outPixmap3);

}

void xrayImaging::on_pushButton_takePicture_clicked()
{

    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->searchAndLock();
    imageCapture->capture();
    camera->unlock();

}

void xrayImaging::on_pushButton_3_clicked()
{
    camera->stop();
    delete mediaRecorder;
    delete imageCapture;
    delete camera;

    hide();
    secondxrayview *x = new secondxrayview(patientid1);
    x->showFullScreen();
}

void xrayImaging::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_S && Qt::Key_Control){
        login = new logIn;
        login->show();
    }
    if (event->key() == Qt::Key_Escape){
        delete mediaRecorder;
        delete imageCapture;
        delete camera;
        camera->stop();
        close();
    }
    if (event->key() == Qt::Key_Right){
        pRegister.connOpen();
        QSqlQuery query = QSqlQuery(pRegister.db);
        QByteArray outByteArray;
        imageidint++;
        imageidstring = QString::number(imageidint,10);

        if( !query.exec( "SELECT Image from imageTable where PatientId = '"+patientid1+"' and ImageId <= '"+imageidstring+"' order by ImageId desc limit 3"))
           QMessageBox::critical(this,tr("Images"),query.lastError().text());

        if(query.next()){
            outByteArray = query.value(0).toByteArray();
            outPixmap.loadFromData(outByteArray);
        }
        if(query.next()){
            outByteArray= query.value(0).toByteArray();
            outPixmap2.loadFromData( outByteArray );
        }
        if(query.next()){
            outByteArray= query.value(0).toByteArray();
            outPixmap3.loadFromData( outByteArray );
        }
        if(query.next()){
            outByteArray= query.value(0).toByteArray();
            outPixmap4.loadFromData( outByteArray );
        }

        ui->stackedWidget->setCurrentIndex(0);
        pRegister.connClose();
        ui->label_lastimage->setPixmap(outPixmap);
        ui->label_first->setPixmap(outPixmap2);
        ui->label_second->setPixmap(outPixmap3);
        ui->label_third->setPixmap(outPixmap4);

    }
    if (event->key() == Qt::Key_Left){
        pRegister.connOpen();
        QSqlQuery query = QSqlQuery(pRegister.db);
        QByteArray outByteArray;
        imageidint--;
        imageidstring = QString::number(imageidint,10);

         if( !query.exec( "SELECT Image from imageTable where PatientId = '"+patientid1+"' and ImageId <= '"+imageidstring+"' order by ImageId desc limit 4"))
            QMessageBox::critical(this,tr("Images"),query.lastError().text());

       // if( !query.exec( "SELECT Image from imageTable where PatientId = '"+PatientId+"' and ImageId = '"+imageidstring+"'"))
         //          QMessageBox::critical(this,tr("Images"),query.lastError().text());

        if(query.next()){
            outByteArray = query.value(0).toByteArray();
            outPixmap.loadFromData( outByteArray );
        }
       if(query.next()){
            outByteArray= query.value(0).toByteArray();
            outPixmap2.loadFromData( outByteArray );
        }
        if(query.next()){
            outByteArray= query.value(0).toByteArray();
            outPixmap3.loadFromData( outByteArray );
        }
        if(query.next()){
            outByteArray= query.value(0).toByteArray();
            outPixmap4.loadFromData( outByteArray );
        }

        ui->stackedWidget->setCurrentIndex(0);
        pRegister.connClose();
        ui->label_lastimage->setPixmap(outPixmap);
        ui->label_first->setPixmap(outPixmap2);
        ui->label_second->setPixmap(outPixmap3);
        ui->label_third->setPixmap(outPixmap4);

    }
}
void xrayImaging::on_pushButton_printer_clicked()
{
    QString lname,fname;
    int w=ui->label_first->width();
    int h=ui->label_first->height();
    pRegister.connOpen();
    QSqlQuery query = QSqlQuery(pRegister.db);
    if( !query.exec( "SELECT FirstName,LastName from patientTable where PatientId = '"+patientid1+"'"))
        qDebug() << "Error getting image from table:\n" << query.lastError();
    if(query.next()){
     fname = query.value(0).toString();
     lname = query.value(1).toString();
       }

      QPrinter printer;
      printer.setPrinterName("Sony UP-D897");
      QPainter painter;
      painter.begin(&printer);
      double xscale = printer.pageRect().width() / double(outPixmap.width());
        double yscale = printer.pageRect().height() / double(outPixmap.height());
        double scale = qMin(xscale, yscale);
        painter.translate(printer.paperRect().x() + printer.pageRect().width() / 2,
                          printer.paperRect().y() + printer.pageRect().height() / 2);
        painter.scale(scale, scale);
        painter.translate(-outPixmap.width()/2, -outPixmap.height()/2);
      painter.drawPixmap(0, 0, outPixmap);
     // painer.drawText(QRect(0, 0, w, h), Qt::AlignHCenter, "Titan Imaging \n Hospitals name, Doctors name \n"+QDateTime::currentDateTime().toString()+"\n"+fname+","+lname+"\n"+patientid1);
      painter.end();

      painter.begin(&printer);
      painter.drawText(QRect(0, 0, w, h), Qt::AlignCenter, "Titan Imaging \n Hospitals name, Doctors name \n"+QDateTime::currentDateTime().toString()+"\n"+fname+","+lname+"\n"+patientid1);
      painter.end();





}
