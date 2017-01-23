#ifndef secondxrayview_H
#define secondxrayview_H

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
#include <QKeyEvent>
#include "login.h"
#include "patientregistration.h"

namespace Ui {
class secondxrayview;
}

class secondxrayview : public QDialog
{
    Q_OBJECT

public:
    QString patientid1,lname;
    explicit secondxrayview(QString x,QWidget *parent = 0);
    ~secondxrayview();

private slots:
    void processCapturedImage(int requestId, const QImage &img);
    void setCamera(const QCameraInfo &cameraInfo);
    void on_pushButton_home_clicked();
    void on_pushButton_takePicture_clicked();
    void on_pushButton_original_clicked();
    void on_pushButton_settings_clicked();

private:
    Ui::secondxrayview *ui;
    QCamera *camera;
    QCameraImageCapture *imageCapture;
    QMediaRecorder *mediaRecorder;
    QCameraImageProcessing *imageProcessing;
    QCameraFocus *focus;
    logIn *login;
    patientRegistration pRegister;
    QPixmap outPixmap = QPixmap();
    QByteArray inByteArray, outByteArray;
    void keyPressEvent(QKeyEvent *event);

};

#endif // secondxrayview_H
