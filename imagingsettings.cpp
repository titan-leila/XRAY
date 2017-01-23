#include "imagingsettings.h"
#include "ui_imagingsettings.h"
#include "secondxrayview.h"




imagingSettings::imagingSettings(QCamera *camera,QCameraImageProcessing *imageProcessing,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::imagingSettings),
    imageProcessing(imageProcessing),
    camera(camera)
{
    ui->setupUi(this);

}


imagingSettings::~imagingSettings()
{
    delete ui;
}


void imagingSettings::on_verticalSlider_brightness_valueChanged(int value)
{
    double x = value;
    double newvalue=x/10;
    imageProcessing =  camera->imageProcessing();
    imageProcessing->setBrightness(newvalue);
}

void imagingSettings::on_verticalSlider_contrast_valueChanged(int value)
{
    double x = value;
    double newvalue=x/10;
    imageProcessing =  camera->imageProcessing();
    imageProcessing->setContrast(newvalue);
}

void imagingSettings::on_verticalSlider_denoise_valueChanged(int value)
{
    double x = value;
    double newvalue=x/10;
    imageProcessing =  camera->imageProcessing();
    imageProcessing->setDenoisingLevel(newvalue);
}

void imagingSettings::on_verticalSlider_zoom_valueChanged(int value)
{

    Q_UNUSED(value);
/*
    double x = value;
    double newvalue=x/10;
    focus = camera->focus();
    focus->digitalZoomChanged(newvalue);
    */
}

void imagingSettings::on_verticalSlider_saturation_valueChanged(int value)
{
    double x = value;
    double newvalue=x/10;
    imageProcessing =  camera->imageProcessing();
    imageProcessing->setSaturation(newvalue);
}

void imagingSettings::on_verticalSlider_sharpening_valueChanged(int value)
{
    double x = value;
    double newvalue=x/10;
    imageProcessing =  camera->imageProcessing();
    imageProcessing->setSharpeningLevel(newvalue);
}

void imagingSettings::on_pushButton_11_send_clicked()
{

}

void imagingSettings::on_pushButton_3_resetimage_clicked()
{
    //set back to original image
}
