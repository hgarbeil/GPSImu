#ifndef MYIMAGEWIDGET_H
#define MYIMAGEWIDGET_H

#include <QWidget>

class MyImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyImageWidget(QWidget *parent = 0);
    void makeQImage3 (unsigned char  *data, int ns, int nl) ;
    void paintEvent (QPaintEvent *);
    void resizeEvent (QResizeEvent *);
    void getXY (float lat, float lon, int *x, int *y) ;
    float radians (float) ;
    void setGPSLoc (float lat, float lon, float heading) ;
    QImage *qimage ;
    unsigned char *imdata ;
    int ns, nl, nsim, nlim ;
    int x_gps, y_gps, x_start_gps, y_start_gps, x_end_gps, y_end_gps ;
    float startLat, startLon, latSpace, lonSpace, scaleX, scaleY ;
    float lat_gps, lon_gps ;
    bool gpsFlag ;
    
signals:
    
public slots:
    
};

#endif // MYIMAGEWIDGET_H
