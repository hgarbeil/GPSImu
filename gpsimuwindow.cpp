#include "gpsimuwindow.h"
#include "ui_gpsimuwindow.h"
#include <QFile>
#include <QDebug>

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
    QFile qf ("C:\\hg\\oahu_geo_byte") ;

    qf.open (QIODevice::ReadOnly) ;
    int nbytesToRead = 2048 * 4096 * 3 ;
    uchar *data = new uchar [nbytesToRead] ;
    int status = qf.read ((char *)&data[0], nbytesToRead) ;
    qf.close () ;


    //QFile1 qf1 ("C:\\hg\\oahu_geo_byte") ;
    //qf1.write
    //qDebug() << "entering makeQImage3" ;
    ui->imageDisplay->makeQImage3 (data, 4096, 2048) ;
    ui->imageDisplay->setGPSLoc (21.35, -157.89, 180.);




    //delete [] data ;
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
    QString gpsTime = *(qgps->timestring) ;
    ui->timeLE->setText(gpsTime) ;
    ui->headingSlider->setValue (qgps->heading) ;
    ui->rollSlider->setValue (qgps->roll) ;
    ui->pitchSlider->setValue (qgps->pitch) ;
    latval = qgps->latVal ;
    lonval = qgps->lonVal ;
    altval = qgps->altVal ;
    QString str = QString ("%1").arg(latval, 10, 'f', 3) ;
    ui->latLE->setText (str) ;
    str = QString ("%1").arg(lonval, 11, 'f', 3) ;
    ui->lonLE->setText (str) ;
    str = QString ("%1").arg(altval, 11, 'f', 3) ;
    ui->altLE->setText (str) ;
    str = QString ("%1").arg(qgps->fix) ;
    ui->fixLE->setText (str) ;
    str = QString ("%1").arg(qgps->nSats) ;
    ui->numsatLE->setText (str) ;

    if (qgps->fix > 0) {
        ui->imageDisplay->setGPSLoc (latval, -1.*lonval, qgps->heading);
        ui->imageDisplay->repaint() ;
    }
    else
        ui->imageDisplay->setGPSLoc (latval, -1.*lonval, qgps->heading);
        //ui->imageDisplay->setGPSLoc (21.35, -157.89, 180.);


}
