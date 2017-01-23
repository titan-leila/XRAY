#include "images.h"
#include "ui_images.h"
#include <QPixmap>
#include <QMessageBox>



Images::Images(QString x,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Images)
{
    ui->setupUi(this);
   PatientId = x;
    registration.connOpen();
    QSqlQuery query = QSqlQuery(registration.db);
    QByteArray outByteArray;
    if( !query.exec( "SELECT ImageId,Image from imageTable where PatientId = '"+PatientId+"' order by ImageId DESC limit 4"))
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
    if(query.next()){;
        outByteArray = query.value(1).toByteArray();
        outPixmap4.loadFromData( outByteArray );
       }
    registration.connClose();
    ui->label_first->setPixmap(outPixmap);
    ui->label_second->setPixmap(outPixmap2);
    ui->label_third->setPixmap(outPixmap3);
    ui->label_fourth->setPixmap(outPixmap4);
}

Images::~Images()
{
    delete ui;
}

void Images::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_S && Qt::Key_Control){
        login = new logIn;
        login->show();
    }
    if (event->key() == Qt::Key_Escape){
        close();
    }
    if (event->key() == Qt::Key_Right){
        registration.connOpen();
        QSqlQuery query = QSqlQuery(registration.db);
        QByteArray outByteArray;
        imageidint++;
        imageidstring = QString::number(imageidint,10);
        qDebug() << imageidstring;
        qDebug() << PatientId;

        if( !query.exec( "SELECT Image from imageTable where PatientId = '"+PatientId+"' and ImageId <= '"+imageidstring+"' order by ImageId desc limit 4"))
           QMessageBox::critical(this,tr("Images"),query.lastError().text());

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
         outByteArray = query.value(0).toByteArray();
         outPixmap4.loadFromData( outByteArray );
           }

        registration.connClose();
        ui->label_first->setPixmap(outPixmap);
        ui->label_second->setPixmap(outPixmap2);
        ui->label_third->setPixmap(outPixmap3);
        ui->label_fourth->setPixmap(outPixmap4);
    }
    if (event->key() == Qt::Key_Left){
        registration.connOpen();
        QSqlQuery query = QSqlQuery(registration.db);
        QByteArray outByteArray;
        imageidint--;
        imageidstring = QString::number(imageidint,10);

         if( !query.exec( "SELECT Image from imageTable where PatientId = '"+PatientId+"' and ImageId <= '"+imageidstring+"' order by ImageId desc limit 4"))
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
            outByteArray = query.value(0).toByteArray();
            outPixmap4.loadFromData( outByteArray );
           }

        ui->label_first->setPixmap(outPixmap);
        ui->label_second->setPixmap(outPixmap2);
        ui->label_third->setPixmap(outPixmap3);
        ui->label_fourth->setPixmap(outPixmap4);


/*
        outPixmap6=outPixmap;
        outPixmap7=outPixmap2;
        outPixmap8=outPixmap3;
        registration.connClose();
        ui->label_first->setPixmap(outPixmap5);
        ui->label_second->setPixmap(outPixmap6);
        ui->label_third->setPixmap(outPixmap7);
        ui->label_fourth->setPixmap(outPixmap8);
        outPixmap=outPixmap5;
        outPixmap2=outPixmap6;
        outPixmap3=outPixmap7;
*/

    }
}


