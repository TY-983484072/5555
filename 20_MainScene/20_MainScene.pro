#-------------------------------------------------
#
# Project created by QtCreator 2020-11-10T21:56:26
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 20_MainScene
TEMPLATE = app


SOURCES += main.cpp\
        mainscene.cpp \
    mypushbutton.cpp \
    selectlevel.cpp \
    playgame.cpp \
    mycoin.cpp \
    dataconfig.cpp

HEADERS  += mainscene.h \
    mypushbutton.h \
    selectlevel.h \
    playgame.h \
    mycoin.h \
    dataconfig.h

FORMS    += mainscene.ui

RESOURCES += \
    rec.qrc
