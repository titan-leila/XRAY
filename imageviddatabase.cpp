#include "imageviddatabase.h"
#include "ui_imageviddatabase.h"
#include "patientregistration.h"
#include "mainmenu.h"

ImageVidDatabase::ImageVidDatabase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageVidDatabase)
{
    ui->setupUi(this);
    patientRegistration x;
    QSqlQueryModel *modal = new QSqlQueryModel();
    x.connOpen();

    QSqlQuery *qry = new QSqlQuery(x.db);
    qry->prepare("select * from imageTable");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_image->setModel(modal);

    x.connClose();

}

ImageVidDatabase::~ImageVidDatabase()
{
    delete ui;
}

void ImageVidDatabase::on_pushButton_home_clicked()
{
    hide();
    mainMenu *x = new mainMenu;
    x->showFullScreen();
}
