#include "videos.h"
#include "ui_videos.h"

Videos::Videos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Videos)
{
    ui->setupUi(this);
}

Videos::~Videos()
{
    delete ui;
}
