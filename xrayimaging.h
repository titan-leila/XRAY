#ifndef XRAYIMAGING_H
#define XRAYIMAGING_H

#include <QDialog>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QMediaRecorder>
#include <QMediaPlayer>
#include <QDebug>
#include <QtSql>
#include <QMediaService>
#include <QMediaMetaData>
#include <QCameraImageCapture>
#include <QShortcut>
#include <QCameraImageProcessing>
#include <QCameraFocus>
#include <QCameraZoomControl>
#include <QKeyEvent>
#include "login.h"
#include "patientregistration.h"
#include "secondxrayview.h"

namespace Ui {
class xrayImaging;
}

class xrayImaging : public QDialog
{
    Q_OBJECT

public:
    QString patientid1,lname,imageidstring;
    int imageidint;
    QPixmap outPixmap = QPixmap();
    QPixmap outPixmap2 = QPixmap();
    QPixmap outPixmap3 = QPixmap();
    QPixmap outPixmap4 = QPixmap();
    explicit xrayImaging(QString x,QWidget *parent = 0);
    ~xrayImaging();

private slots:
    void processCapturedImage(int requestId, const QImage &img);
    void setCamera(const QCameraInfo &cameraInfo);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_takePicture_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_printer_clicked();

private:
    Ui::xrayImaging *ui;
    QByteArray inByteArray, outByteArray;
    QCamera *camera;
    QCameraImageCapture *imageCapture;
    QMediaRecorder *mediaRecorder;
    QCameraImageProcessing *imageProcessing;
    QCameraFocus *focus;
    logIn *login;
    patientRegistration pRegister;
    void keyPressEvent(QKeyEvent *event);

    bool isCapturingImage;
    bool applicationExiting;
};

#endif // XRAYIMAGING_H
