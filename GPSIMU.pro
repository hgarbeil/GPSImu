#-------------------------------------------------
#
# Project created by QtCreator 2015-10-18T09:59:19
#
#-------------------------------------------------

QT       += core gui serialport opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GPSIMU
TEMPLATE = app


SOURCES += main.cpp\
        gpsimuwindow.cpp \
    myglwidget.cpp \
    qgpsdevice.cpp

HEADERS  += gpsimuwindow.h \
    myglwidget.h \
    qgpsdevice.h

FORMS    += gpsimuwindow.ui

#LIBS += libQt5OpenGL.a
