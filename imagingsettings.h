#ifndef IMAGINGSETTINGS_H
#define IMAGINGSETTINGS_H
#include "xrayimaging.h"
#include <QCameraImageProcessing>
#include <QCamera>
#include <QDialog>

namespace Ui {
class imagingSettings;
}

class imagingSettings : public QDialog
{
    Q_OBJECT

public:
    explicit imagingSettings(QCamera *camera,QCameraImageProcessing *imageProcessing, QWidget *parent = 0);
    ~imagingSettings();

private slots:

    void on_verticalSlider_brightness_valueChanged(int value);

    void on_verticalSlider_contrast_valueChanged(int value);

    void on_verticalSlider_sharpening_valueChanged(int value);

    void on_verticalSlider_zoom_valueChanged(int value);

    void on_verticalSlider_saturation_valueChanged(int value);

    void on_verticalSlider_denoise_valueChanged(int value);

    void on_pushButton_11_send_clicked();

    void on_pushButton_3_resetimage_clicked();

private:
    Ui::imagingSettings *ui;
    QCameraImageProcessing *imageProcessing;
    QCamera *camera;
};

#endif // IMAGINGSETTINGS_H
