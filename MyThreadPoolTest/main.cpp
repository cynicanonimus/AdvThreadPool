/*
 This file is part of project AdvThreadPool.

    AdvThreadPool is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License.

    AdvThreadPool is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with pdb.  If not, see <http://www.gnu.org/licenses/>.
*/
//
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
    const AdvThreadPool::PoolMode en_mode = AdvThreadPool::en_FIFO; // or change it to AdvThreadPool::en_FIFO and see how does it works
    //
    const int i_threads_number      = 2; //"0" means "set optimal amount automatically"
    const int jobs_total_number     = 20;
    const int i_long_job_time_sec   = 1;
    const int i_short_job_time_sec  = 1;
    //
    AdvThreadPool::getInstance().init(i_threads_number);
    AdvThreadPool::getInstance().setMode(en_mode);
    //
    int i_delay = i_short_job_time_sec;
    //
    for (int i = 0; i < jobs_total_number; i++)
    {
        //
        //imitate execution of jobs with the different execution time
        //
        if (AdvThreadPool::en_FIFO == en_mode)
        {
            if( i%10 == 0 )
            {
                i_delay = i_long_job_time_sec;
            }
            else
                i_delay = i_short_job_time_sec;
        };
        JobForTests* ptr_job = new JobForTests(i, i_delay);
        //
        //for demonstration PRIO mode
        //
        if( i%10 == 0 && (AdvThreadPool::en_PRIO == en_mode) )
        {
            ptr_job->setPriority(QThread::NormalPriority);
        };
        //
        AdvThreadPool::getInstance().execute(ptr_job);
    };
    //
    std::cout<<"Waiting for the queue finish...."<<std::endl;
    AdvThreadPool::getInstance().stop();
    //
    std::cout<<"Test done."<<std::endl;
    //
    return a.exec();
}
