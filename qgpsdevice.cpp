#include "qgpsdevice.h"
#include <QDebug>
#include <QString>

QGPSDevice::QGPSDevice(QObject *parent) :
    QObject(parent)
{
    qsport = new QSerialPort (this) ;
    qsport->setPortName ("COM13") ;

    indata = new QByteArray () ;
    indata->reserve (1280) ;

    connect (qsport, SIGNAL (readyRead()), this, SLOT (readData())) ;
    //this->init() ;
    clearNext = false ;
    latVal = 0. ;
    lonVal = 0. ;

    fixFlag = false ;
    fix = 0 ;
    outString ="" ;
    timestring = new QString("");
    posstring = new QString("No Fix") ;
    gpsStatus = true ;
    nSats = 0 ;
    pitch = 0 ;
    roll = 0. ;
    heading = 0. ;
}


void QGPSDevice::setPort (QString name){
    qsport->setPortName (name) ;

}

QGPSDevice::~QGPSDevice () {
    if (qsport->isOpen()) {
        qsport->close() ;
    }
}

void QGPSDevice::init (){
    int status ;
    status = qsport->open (QIODevice::ReadWrite) ;
    qsport->setBaudRate (115200) ;
    qDebug()<< "Serial port status is " << status  ;
    qsport->flush() ;


}

void QGPSDevice::readData() {
    int sz ;
    QByteArray data = qsport->readAll () ;
    //qDebug() << data ;
    qsport->flush() ;
    if (clearNext ) {
        indata->clear() ;
        clearNext = false ;
    }

    indata->append (data) ;
    sz = indata->size() ;
    //qDebug() << indata->constData() ;
    if (indata->contains("\n") & indata->contains("$")){
        //qDebug() << indata->constData() ;
        int findPos = indata->indexOf ('\n') ;
        QString gString0 = indata->left(findPos) ;
        findPos = gString0.indexOf("$") ;
        QString gString = gString0.right(findPos);
        clearNext = true ;
        sz = gString.size() ;
        //qDebug() << indata->constData() << "size is " << sz  ;
        //qDebug() << indata->constData() << "size is " << sz  ;
        if (sz < 240)
            parseVals (gString0.toLatin1().data()) ;
            //parseGPS (indata->constData()) ;
    }


}

void QGPSDevice::parseVals(const char *indata){

    //qDebug() << indata  ;
    QString *str = new QString(indata) ;
    QStringList toked = str->split(" ") ;
    int nitems = toked.count() ;
    if (nitems < 12)
        return ;
    *timestring = toked[1] ;
    heading = toked[9].toFloat() ;
    pitch = toked[10].toFloat()/10. ;
    roll = toked [11].toFloat()/10. ;
    emit(updateVals()) ;

}


void QGPSDevice::parseGPS(const char *indata){
    int latdeg, nchars ;
    char *tmpstr, latCH[80], lonCH[80], indat[1280] ;
    nchars = sizeof(indata) ;
    strcpy (indat, indata) ;
    bool GGAFlag = false ;
    bool GSAFlag = false ;
    if (strstr(indat, "$GPGGA")) GGAFlag = true ;
    if (strstr(indat, "$GPGSA")) GSAFlag = true ;
    //if (!fixFlag)


    if (strstr(indat, "$GPGGA")){
        tmpstr = strtok (indat, ",") ;
        tmpstr = strtok (NULL, ",") ;
        if (strlen (tmpstr)>0){
            gpsTime = atof (tmpstr) ;
            //qDebug () <<  gpsTime ;
            parseTime (gpsTime) ;
        }
        tmpstr = strtok (NULL, ",") ;
        if (strlen(tmpstr)<5) return ;

        this->latVal = atof (tmpstr) ;

        tmpstr = strtok (NULL, ",") ;
        qDebug() << "LATCH is : " << tmpstr ;

        strcpy (latCH, tmpstr) ;
        /*
        if (strlen (tmpstr) > 0){
            if (strstr(tmpstr,"S")){
                this->latVal *= -1. ;
            }
        }
        */
        tmpstr = strtok (NULL, ",") ;
        this->lonVal = atof (tmpstr) ;

        tmpstr = strtok (NULL, ",") ;
        strcpy (lonCH, tmpstr);

        tmpstr = strtok (NULL, ",");
        if (strlen (tmpstr) > 0){
            this->fix = atoi (tmpstr) ;
            qDebug () << "fix is " << this->fix ;

        }
        tmpstr = strtok (NULL, ",");
        if (strlen (tmpstr) > 0){
            this->nSats = atoi (tmpstr) ;

        }
        // horiz dilution
        tmpstr = strtok (NULL, ",");
        // altitude
        tmpstr = strtok (NULL, ",");
        if (strlen (tmpstr) > 0){
            this->altVal = atof (tmpstr) ;

        }
        //posstring->sprintf ("%f %s %f %s %f", latVal, latCh, lonVal, lonCh, altVal) ;
        *posstring = QString("%1 %2 %3 %4 %5").arg(latVal,9,'f',3).arg(latCH).arg(lonVal, 10, 'f',3).arg(lonCH).arg(altVal) ;
    }




}


void QGPSDevice::parseTime (float tim){
    QString teststr ;
    int loc_hr, loc_min ;
    float loc_sec ;
    loc_hr = int (tim / 1.0E4) ;
    loc_min = int ((tim - (loc_hr * 1.0E4)) / 100) ;
    loc_sec = tim- (hr * 1.0E4)-(loc_min*100) ;

    QChar z ('0') ;
    *timestring = QString ("%1%2%3").arg(loc_hr,2,10,z).arg(loc_min,2,10,z).arg(loc_sec,4,'f',1,z) ;
    hr = loc_hr ;
    min = loc_min ;
    sec = loc_sec ;


}
