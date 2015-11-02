#ifndef GPSIMUWINDOW_H
#define GPSIMUWINDOW_H

#include <QWidget>
#include "qgpsdevice.h"

namespace Ui {
class GPSIMUWindow;
}

class GPSIMUWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit GPSIMUWindow(QWidget *parent = 0);
    ~GPSIMUWindow();
    QGPSDevice *qgps ;
protected:
    void changeEvent(QEvent *e);
    
private:
    Ui::GPSIMUWindow *ui;

public slots :
    void pitchChanged(int) ;
    void rollChanged(int) ;
    void yawChanged(int);
    void updateGPSVals() ;
};

#endif // GPSIMUWINDOW_H
