#ifndef IMAGES_H
#define IMAGES_H
#include "patientregistration.h"
#include "login.h"
#include <QKeyEvent>
#include <QDialog>

namespace Ui {
class Images;
}

class Images : public QDialog
{
    Q_OBJECT

public:
    QPixmap outPixmap = QPixmap();
    QPixmap outPixmap2 = QPixmap();
    QPixmap outPixmap3 = QPixmap();
    QPixmap outPixmap4 = QPixmap();
    QPixmap outPixmap5 = QPixmap();
    QPixmap outPixmap6 = QPixmap();
    QPixmap outPixmap7 = QPixmap();
    QPixmap outPixmap8 = QPixmap();
    QString imageidstring,PatientId;
    int imageidint;
    explicit Images(QString x, QWidget *parent = 0);
    ~Images();

private slots:


private:

    Ui::Images *ui;
    patientRegistration registration;
    logIn *login;
    void keyPressEvent(QKeyEvent *event);
};

#endif // IMAGES_H
