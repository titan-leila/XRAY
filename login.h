#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "settings.h"

namespace Ui {
class logIn;
}

class logIn : public QDialog
{
    Q_OBJECT

public:
    explicit logIn(QWidget *parent = 0);
    ~logIn();

private slots:
    void on_pushButton_clicked();

private:
    Ui::logIn *ui;
    Settings *settings;
};

#endif // LOGIN_H
