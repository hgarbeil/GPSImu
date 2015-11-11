#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QTimer>

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0);
    QTcpSocket *client ;
   // QTimer *qtimer ;
    QString logFileName, filePrefix ;
    QFile *logFile ;
    int lastday, curday ;

    int count ;
signals:
    void gotData (QString) ;

public slots:
    void startRead () ;

    void acceptConnection () ;
    void close () ;


};

#endif // MYTCPSERVER_H
