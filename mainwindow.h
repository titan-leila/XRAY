#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopServices>
#include <QUrl>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QSplashScreen>
#include <QTimer>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QSql>
#include <QDateTime>
#include <QWidget>
#include <QDebug>
#include <QDir>
#include <QPixmap>
#include <QDialog>
#include <QOpenGLContext>
#include "mainmenu.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_checkBox_12_clicked();

private:
    Ui::MainWindow *ui;
    mainMenu *menuPage;
};

#endif // MAINWINDOW_H
