#include "myimagewidget.h"
#include <QPainter>
#include <QDebug>
#include "math.h"

#define PI atan(1.)*4.
MyImageWidget::MyImageWidget(QWidget *parent) :
    QWidget(parent)
{
    qimage = 0L ;
    startLat = 21.5435124 ;
    startLon = -158.29578234 ;
    latSpace = .0001467 ;
    lonSpace = .00014467 ;
    gpsFlag = false ;
}

void MyImageWidget::resizeEvent (QResizeEvent *re){


    ns  = this->width () ;
    nl = this->height () ;
    scaleX = float(this->nsim) / ns ;
    scaleY = float(this->nlim) / nl ;


}

void MyImageWidget::getXY (float lat, float lon, int *x, int *y){

    float ydiff, xdiff ;
    *y = (startLat - lat) / latSpace / scaleY  ;
    *x = (lon - startLon) / lonSpace / scaleX ;

}


void MyImageWidget::setGPSLoc (float lat, float lon, float heading){
    float xoff, yoff, arcHead ;
    lat_gps = lat ;
    lon_gps = lon ;
    gpsFlag = true ;
    arcHead = radians (heading) ;
    xoff = 12. * sin(arcHead) ;
    yoff = 12. * cos(arcHead) ;
    getXY (lat_gps, lon_gps, &x_gps, &y_gps) ;
    x_start_gps = x_gps + xoff ;
    y_start_gps = y_gps - yoff ;
    x_end_gps = x_gps - xoff * .7 ;
    y_end_gps = y_gps + yoff * .7 ;
    repaint() ;
}


void MyImageWidget::makeQImage3 (unsigned char *data, int nsim, int nlim){


    int  ib, locns, locnl ;
    long i ;
    float min = 1.E9, max = -1.E9 ;
    float fval, scale ;
    long index, nPix = nsim * nlim ;

    this->nsim = nsim ;
    this->nlim = nlim ;

    locns  = this->width () ;
    locnl = this->height () ;

    scaleX = this->nsim / locns ;
    scaleY = this->nlim / locnl ;

    imdata = new unsigned char [nsim * nlim * 4] ;




    for (ib=0; ib<3;  ib++) {
        for (i=0; i<nPix; i++){
            index = ib * nPix ;
            imdata [i*4+(ib)] = uchar(int(data[index + i])*2) ;
            if (ib==0) imdata[i*4+3] = 0xff ;

        }

    }


    qimage = new QImage ((uchar *)&imdata[0], nsim, nlim, nsim * 4, QImage::Format_ARGB32) ;

    repaint () ;


}


void MyImageWidget::paintEvent(QPaintEvent *){
    QPainter paint (this) ;
    if (!qimage) return ;
        //QPixmap qpm = QPixmap::fromImage (*qimage) ;

    QImage qimnew = qimage->scaled (ns, nl) ;
        //paint.drawImage (0, 0, *qimage, 0, 0, 25, 25) ;
    paint.drawImage (0, 0, qimnew, 0, 0, ns, nl) ;
        //paint.drawPixmap (0, 0, qpm, 0, 0, ns, nl) ;

    paint.setPen (QPen(Qt::yellow)) ;
    if (gpsFlag) {
        paint.drawEllipse (QPoint(x_gps, y_gps), 8, 8) ;

        paint.drawLine ((int)x_start_gps, (int)y_start_gps, (int)x_end_gps, (int)y_end_gps) ;
    }
}

float MyImageWidget::radians(float degs){
    float rads ;
    rads = degs * PI / 180. ;
    return rads ;
}
