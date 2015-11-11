#include "mytcpserver.h"
#include <iostream>
#include <QDate>
using namespace std;

MyTcpServer::MyTcpServer(QObject *parent) :
    QTcpServer(parent)
{

    logFile = 0L ;
    lastday = -1 ;
    //qtimer = 0L ;
    filePrefix = "";


}


void MyTcpServer::startRead () {
    //QString outstr ;
    QDate date ;
    int nbytes ;
    char outbuff [48] ;
    char buffer[8192] = {0};
    nbytes = client->bytesAvailable () ;
    if (nbytes <2) return ;
    if (nbytes > 8191){
        cout << "Potential buffer overrun" << endl ;
        cout << "reading 8191 bytes " << endl ;
        nbytes = 8191 ;
    }
    client->read(buffer, nbytes);
    sprintf (outbuff, "Received %d", nbytes) ;
    QString *outstr = new QString (buffer) ;

    emit (gotData (*outstr)) ;


}


void MyTcpServer::acceptConnection()
{

  client = nextPendingConnection();

  connect(client, SIGNAL(readyRead()), this, SLOT(startRead()));



//client->write ("Connected") ;
}


void MyTcpServer::close () {
    if (logFile) logFile->close () ;
    QTcpServer::close () ;


}
