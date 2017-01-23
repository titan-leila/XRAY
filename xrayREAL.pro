#-------------------------------------------------
#
# Project created by QtCreator 2016-07-25T11:05:43
#
#-------------------------------------------------

QT       += core gui sql printsupport multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = xrayREAL
TEMPLATE = app



SOURCES += main.cpp\
        mainwindow.cpp \
    mainmenu.cpp \
    xrayimaging.cpp \
    patientregistration.cpp \
    patientdatabase.cpp \
    hyperion.cpp \
    imagingsettings.cpp \
    imageviddatabase.cpp \
    images.cpp \
    videos.cpp \
    ivdb.cpp \
    settings.cpp \
    secondxrayview.cpp \
    login.cpp

HEADERS  += mainwindow.h \
    mainmenu.h \
    xrayimaging.h \
    patientregistration.h \
    patientdatabase.h \
    hyperion.h \
    imagingsettings.h \
    imageviddatabase.h \
    images.h \
    videos.h \
    ivdb.h \
    settings.h \
    secondxrayview.h \
    login.h

FORMS    += mainwindow.ui \
    mainmenu.ui \
    xrayimaging.ui \
    patientregistration.ui \
    patientdatabase.ui \
    hyperion.ui \
    imagingsettings.ui \
    imageviddatabase.ui \
    images.ui \
    videos.ui \
    ivdb.ui \
    settings.ui \
    secondxrayview.ui \
    login.ui

RESOURCES += \
    resource.qrc
