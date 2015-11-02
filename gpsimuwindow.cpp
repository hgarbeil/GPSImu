#include "gpsimuwindow.h"
#include "ui_gpsimuwindow.h"

GPSIMUWindow::GPSIMUWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GPSIMUWindow)
{
    ui->setupUi(this);
    connect (ui->myGLWidget, SIGNAL(pitchChanged(int)), this, SLOT(pitchChanged(int))) ;
    connect (ui->myGLWidget, SIGNAL(yawChanged(int)), this, SLOT(yawChanged(int))) ;
    connect (ui->myGLWidget, SIGNAL(rollChanged(int)), this, SLOT(rollChanged(int))) ;
    qgps = new QGPSDevice () ;
    qgps->init() ;
    connect (qgps, SIGNAL(updateVals()), this, SLOT(updateGPSVals())) ;
}

GPSIMUWindow::~GPSIMUWindow()
{
    delete ui;
}

void GPSIMUWindow::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void GPSIMUWindow::pitchChanged (int val){
    QString str = QString("%1").arg(val) ;
    ui->pitchLabel->setText(str) ;

}


void GPSIMUWindow::yawChanged (int val){
    QString str = QString("%1").arg(val) ;
    ui->yawLabel->setText(str) ;

}

void GPSIMUWindow::rollChanged (int val){
    QString str = QString("%1").arg(val) ;
    ui->rollLabel->setText(str) ;

}


void GPSIMUWindow::updateGPSVals() {
    QString gpsTime = *qgps->timestring ;
    ui->timeLE->setText(gpsTime) ;
    ui->headingSlider->setValue (qgps->heading) ;
    ui->rollSlider->setValue (qgps->roll) ;
    ui->pitchSlider->setValue (qgps->pitch) ;

}
