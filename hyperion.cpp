#include "hyperion.h"
#include "ui_hyperion.h"

hyperion::hyperion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hyperion)
{
    ui->setupUi(this);
}

hyperion::~hyperion()
{
    delete ui;
}
