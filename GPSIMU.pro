#-------------------------------------------------
#
# Project created by QtCreator 2015-10-18T09:59:19
#
#-------------------------------------------------

QT       += core gui serialport opengl network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GPSIMU
TEMPLATE = app


SOURCES += main.cpp\
        gpsimuwindow.cpp \
    myglwidget.cpp \
    qgpsdevice.cpp \
    myimagewidget.cpp \
    mytcpserver.cpp

HEADERS  += gpsimuwindow.h \
    myglwidget.h \
    qgpsdevice.h \
    myimagewidget.h \
    mytcpserver.h

FORMS    += gpsimuwindow.ui

#LIBS += libQt5OpenGL.a
