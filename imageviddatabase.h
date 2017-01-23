#ifndef IMAGEVIDDATABASE_H
#define IMAGEVIDDATABASE_H

#include <QDialog>
#include "images.h"

namespace Ui {
class ImageVidDatabase;
}

class ImageVidDatabase : public QDialog
{
    Q_OBJECT

public:
    explicit ImageVidDatabase(QWidget *parent = 0);
    ~ImageVidDatabase();

private slots:

    void on_pushButton_home_clicked();

private:
    Ui::ImageVidDatabase *ui;
    Images *x;
};

#endif // IMAGEVIDDATABASE_H
