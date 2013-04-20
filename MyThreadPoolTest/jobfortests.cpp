#include "jobfortests.h"
//
#include <QTime>
#include <QCoreApplication>
#include <iostream>

JobForTests::JobForTests(int id, int delay, QObject *parent) :
    AdvThreadJob(parent)
{
    m_id = id;
    m_idelay = delay;
}

bool JobForTests::exec()
{
    QTime dieTime= QTime::currentTime().addSecs(m_idelay);
    //
    //QThread::currentThread()->sleep(100);

    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    };
    std::cout<<"executing:----------------------------------["<<m_id<<"]"<<std::endl;
    //
    return true;
}
