#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap("C:/Users/admin/Documents/xrayREALnewxxy/Images/titan1.png"));
    splash->show();
     MainWindow w;
     QTimer::singleShot(3000,splash,SLOT(close()));
     QTimer::singleShot(3000,&w,SLOT(showFullScreen()));
    return a.exec();
}
