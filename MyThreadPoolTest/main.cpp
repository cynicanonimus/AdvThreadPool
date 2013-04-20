#include <QtCore/QCoreApplication>
#include "../AdvThreadPool/advthreadpool.h"
#include "jobfortests.h"
//
#include <QTime>
#include <QCoreApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //
    AdvThreadPool::getInstance().init(3);
    //
    int i_delay = 0;
    //
    for (int i = 0; i < 50; i++)
    {
        //for imitation jobs with the different execution time
        if( i%10 == 0 )
            i_delay = 8;
        else
            i_delay = 1;

        JobForTests* ptr_job = new JobForTests(i, i_delay);
        AdvThreadPool::getInstance().execute(ptr_job);
    };
    //
    AdvThreadPool::getInstance().stop();
    //
    std::cout<<"Test done."<<std::endl;
    //
    return a.exec();
}
