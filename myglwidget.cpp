#include "myglwidget.h"
#include "GL/glu.h"

MyGLWidget::MyGLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
    angleScale = 1. ;


}
static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void MyGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        //emit xRotationChanged(angle);
        emit (pitchChanged(angle)) ;
        updateGL();
    }
}

void MyGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        //emit yRotationChanged(angle);
        emit (yawChanged(angle)) ;
        updateGL();
    }
}

void MyGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        //emit yRotationChanged(angle);
        updateGL();
        emit (rollChanged(angle)) ;
    }
}


void MyGLWidget::initializeGL()
{
    qglClearColor(Qt::black);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);

    //static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    //glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(yRot / angleScale, 0.0, 1.0, 0.0);
    glRotatef(zRot / angleScale, 0.0, 0.0, 1.0);
    glRotatef(xRot / angleScale, 1.0, 0.0, 0.0);


    drawPlane();
}

void MyGLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

void MyGLWidget::draw()
{
    qglColor(Qt::red);
    /*
    glBegin(GL_QUADS);
        glNormal3f(0,0,-1);
        glVertex3f(-1,-1,0);
        glVertex3f(-1,1,0);

    glEnd();
    glColor3ub(255,0,0) ;
    glBegin(GL_TRIANGLES);
        glNormal3f(0,-1,0.707);
        glVertex3f(-1,-1,0);
        glVertex3f(1,-1,0);
        glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(1,0, 0.707);
        glVertex3f(1,-1,0);
        glVertex3f(1,1,0);
        glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(0,1,0.707);
        glVertex3f(1,1,0);
        glVertex3f(-1,1,0);
        glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(-1,0,0.707);
        glVertex3f(-1,1,0);
        glVertex3f(-1,-1,0);
        glVertex3f(0,0,1.2);
    glEnd();
    */
    glBegin( GL_TRIANGLES );
     glColor3f( 255.0f, 0.0f, 0.0f ); glVertex3f( 0.0f, 1.f, 0.0f );
     glColor3f( 0.0f, 1.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 1.0f );
     glColor3f( 0.0f, 0.0f, 1.0f ); glVertex3f( 1.0f, -1.0f, 1.0f);

     glColor3f( 1.0f, 0.0f, 0.0f ); glVertex3f( 0.0f, 1.0f, 0.0f);
     glColor3f( 0.0f, 1.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 1.0f);
     glColor3f( 0.0f, 0.0f, 1.0f ); glVertex3f( 0.0f, -1.0f, -1.0f);

     glColor3f( 1.0f, 0.0f, 0.0f ); glVertex3f( 0.0f, 1.0f, 0.0f);
     glColor3f( 0.0f, 1.0f, 0.0f ); glVertex3f( 0.0f, -1.0f, -1.0f);
     glColor3f( 0.0f, 0.0f, 1.0f ); glVertex3f( 1.0f, -1.0f, 1.0f);


     glColor3f( 1.0f, 0.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 1.0f);
     glColor3f( 0.0f, 1.0f, 0.0f ); glVertex3f( 0.0f, -1.0f, -1.0f);
     glColor3f( 0.0f, 0.0f, 1.0f ); glVertex3f( 1.0f, -1.0f, 1.0f);

     glEnd();

}


void MyGLWidget::drawPlane() {
    //glBegin() ;
    GLUquadric  *obj = gluNewQuadric () ;
    glColor3f(1.,0.,1.) ;
    glTranslatef (0.,0.,-1.5);
    glBegin(GL_TRIANGLES);
        //glNormal3f(-1,0,0.707);
        // right wing

        glVertex3f(-.2,0.,2.);
        glVertex3f(-1.7,0.,.2);
        glVertex3f(-.2,0,0);
        // bot of right wing
        glVertex3f(-.2,0.,0.);
        glVertex3f(-1.7,0.,.2);
        glVertex3f(-.2,0,2);

        //left wing
        glVertex3f(.2,0.,2.);
        glVertex3f(1.7,0.,.2);
        glVertex3f(.2,0,0);
        // bot of left wing
        glVertex3f(.2,0.,0.);
        glVertex3f(1.7,0.,.2);
        glVertex3f(.2,0,2);


        glColor3f (0., 1., .8) ;

        glVertex3f(0,0,1.);
        glVertex3f(0,1.0,0);
        glVertex3f(-.1,0,0);

        glVertex3f(.1,0.,0);
        glVertex3f(0.,1.0,0) ;
        glVertex3f(0.,0.,1);

        glVertex3f(-.1,0.,0);
        glVertex3f(.1,0.,0);
        glVertex3f(0,1.0,0);


        glVertex3f(0,1.0,0.);
        glVertex3f(.1,0,0);
        glVertex3f(-.1,0.,0.);
        glColor3f(0.,.2,.9) ;
    glEnd();
    glColor3f(0.,.2,.9) ;
    gluCylinder (obj, .2,.1, 3, 32,32) ;
    glColor3f(1,1,0) ;
    glTranslatef (0., 0.,3.) ;
    gluSphere (obj,.1, 24,24) ;
    glColor3f(1,0.,0) ;
    glTranslatef (0., 0., -3.) ;
    gluSphere (obj,.2, 24,24) ;

    glFlush() ;
    //glEnd() ;
}


