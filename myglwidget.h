#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QOpenGLFunctions>

class MyGLWidget : public QGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);
    float angleScale ;
protected:
void initializeGL();
void paintGL();
void resizeGL(int width, int height);

private :
    void draw () ;

    void drawPlane() ;
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;
    
signals:
    void pitchChanged(int);
    void rollChanged(int) ;
    void yawChanged(int) ;
    
public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    
};

#endif // MYGLWIDGET_H
