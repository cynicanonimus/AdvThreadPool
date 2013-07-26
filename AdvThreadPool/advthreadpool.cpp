//
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
#include "advthread.h"
#include "advthreadpool.h"
//
#include <QTime>
#include <QCoreApplication>
#include <QMutexLocker>
//
#include <iostream> // only for debug

AdvThreadPool::AdvThreadPool(QObject *parent) :
    QObject(parent)
{
    m_uiMaxThreadNumber = 0;
    m_uiUniquer         = 0;
    m_EnableWork        = false;
    //
    setMode (en_FIFO);
}

AdvThreadPool::~AdvThreadPool()
{
    ThreadMap::Iterator itr;
    for (itr = m_Pool.begin(); itr != m_Pool.end(); ++itr)
    {
        delete itr.value();
    };
    //
    m_Pool.clear();
}

AdvThreadPool& AdvThreadPool::getInstance()
{
    static AdvThreadPool instance;
    //
    return instance;
}

void AdvThreadPool::init(unsigned int ui_threads_amount)
{
    if (m_uiMaxThreadNumber > 0)
        return;
    //
    if (ui_threads_amount > 0)
        m_uiMaxThreadNumber = ui_threads_amount;
    else
        m_uiMaxThreadNumber = QThread::idealThreadCount();
    //
    m_EnableWork = true;
}

void AdvThreadPool::setMode (PoolMode en_mode)
{
    QMutexLocker locker (&m_TaskLocker);
    m_enPoolMode = en_mode;
}

bool AdvThreadPool::execute(AdvThreadJob* ptr_job)
{
    if ( NULL == ptr_job )
        return false;
    //
    if (false == m_EnableWork)
        return false;
    //
    if (getTaskQueueSize() > 0)
    {
        addJobToQueue(ptr_job);
        //std::cout<<"add job N 1, queuse size:"<<getTaskQueueSize()<<std::endl;
        return true;
    };
    //
    AdvThread* ptr_available_thread = getAvailableThread(); // scan threadpool, search available thread
    //
    if (NULL == ptr_available_thread)   // available thread was not found, may be all existing threads are busy
    {
        ptr_available_thread = createReservedThread();
    };
    //
    if (NULL != ptr_available_thread)
    {
        ptr_available_thread->setJob(ptr_job);
        ptr_available_thread->start(ptr_job->getPriority());
    }else
    {
        addJobToQueue(ptr_job);
        //std::cout<<"add job N 2, queuse size:"<<getTaskQueueSize()<<std::endl;
    };
    //
    return true;
}

void AdvThreadPool::stop ()
{
    m_EnableWork = false;
    //
    int i_max_cycle_repeat = 1000;
    int i_current_step = 0;
    //
    while ( true )
    {
        i_current_step++;
        if (i_current_step >=  i_max_cycle_repeat)
            break;
        //
        if ( (isIdle() == false) || (getTaskQueueSize() > 0) )
        {
            sleep(1);
            continue;
        };
    };
    //
    std::cout<<"final queue size:"<<getTaskQueueSize()<<std::endl;
    //
    return;
}

bool AdvThreadPool::isIdle ()
{
    ThreadMap::Iterator itr;
    {
        QMutexLocker thread_locker (&m_PoolLocker);
        //
        for (itr = m_Pool.begin(); itr != m_Pool.end(); ++itr)
        {
            if ( itr.value()->isFinished() == false )
            {
                return false;
            };
        };
    };
    //
    return true;
}

int AdvThreadPool::getTaskQueueSize() const
{
    int i_queue_size = 0;
    //
    QMutexLocker locker (&m_TaskLocker);
    i_queue_size = m_TaskQueue.size();
    //
    return i_queue_size;
}

void AdvThreadPool::addJobToQueue   (AdvThreadJob* ptr_job)
{
    QMutexLocker locker (&m_TaskLocker);
    //
    if (en_FIFO == m_enPoolMode)
    {
        m_TaskQueue.enqueue(ptr_job);
    }else // in this case we are basing on the priority, not FIFO.
    {
        int i_insertion_position = -1;

        for (int i = 0; i< m_TaskQueue.size(); i++)
        {
            AdvThreadJob* ptr_queue_job =  m_TaskQueue.at(i);
            //
            const QThread::Priority queue_prio = ptr_queue_job->getPriority();
            const QThread::Priority job_prio = ptr_job->getPriority();
            //
            if ( queue_prio < job_prio )
            {
                i_insertion_position = i;
                break;
            };
        }
        if (i_insertion_position != -1)
            m_TaskQueue.insert(i_insertion_position, ptr_job);
        else
            m_TaskQueue.enqueue(ptr_job);
    };
}

AdvThreadJob*   AdvThreadPool::extractNextJob ()
{
    QMutexLocker locker (&m_TaskLocker);
    //
    AdvThreadJob* ptr_job = NULL;
    //
    if (m_TaskQueue.size() > 0)
        ptr_job = m_TaskQueue.dequeue();
    //
    return ptr_job;
}

AdvThread*  AdvThreadPool::getAvailableThread ()
{
    AdvThread* ptr_available_thread = NULL;
    QMutexLocker thread_locker (&m_PoolLocker);
    //
    ThreadMap::Iterator itr;
    for (itr = m_Pool.begin(); itr != m_Pool.end(); ++itr)
    {
        if ( itr.value()->isFinished() )
        {
            ptr_available_thread = itr.value();
            break;
        };
    };
    //
    return ptr_available_thread;
}
/*
this is old version, but I will remove it later

*/
void AdvThreadPool::onStandardFinish ()
{
    //QMutexLocker locker (&m_PoolLocker);
    //
/*
    QObject* ptr_sender = QObject::sender();

    std::cout<<"finish triggered, queuse size:"<<getTaskQueueSize()<<std::endl;
    AdvThreadJob* ptr_job = NULL;
    //
    if (getTaskQueueSize() > 0)
    {
        AdvThread* ptr_thread =  AdvThreadPool::getAvailableThread ();
        ptr_job = extractNextJob();
        //
        if (ptr_thread)
        {
            ptr_thread->setJob(ptr_job);
            ptr_thread->start( ptr_job->getPriority() );
        };
*/


/*
        ThreadMap::const_iterator i = m_Pool.constBegin();
        //
        while (i != m_Pool.constEnd())
        {
            bool b_isfinished = i.value()->isFinished();
            bool b_isrunning  = i.value()->isRunning();
            //
            if ( i.value()->isFinished() )
            {
                ptr_job = extractNextJob();
                i.value()->setJob(ptr_job);
                i.value()->start( ptr_job->getPriority() );
            };
            ++i;
        };

    };
*/
    //
    return;
}

void  AdvThreadPool::onCheckFinish ()
{
    QObject* ptr_sender = QObject::sender();

    std::cout<<"finish triggered, queuse size:"<<getTaskQueueSize()<<std::endl;
    AdvThreadJob* ptr_job = NULL;
    //
    if (getTaskQueueSize() > 0)
    {
        AdvThread* ptr_thread =  AdvThreadPool::getAvailableThread ();
        ptr_job = extractNextJob();
        //
        if (ptr_thread)
        {
            ptr_thread->setJob(ptr_job);
            ptr_thread->start( ptr_job->getPriority() );
        };
    };
    //
    return;
}

AdvThread* AdvThreadPool::createReservedThread ()
{
    QMutexLocker thread_locker (&m_PoolLocker);
    //
    AdvThread* ptr_thread = NULL;

    if ((unsigned int) m_Pool.size() < m_uiMaxThreadNumber)    // is it possible to create new one?
    {
        const unsigned int ui_id = ++m_uiUniquer;
        ptr_thread = new AdvThread(ui_id);
        QObject::connect(ptr_thread, SIGNAL(th_finished()), this, SLOT(onCheckFinish() ));
        //
        m_Pool[ui_id] = ptr_thread;
    };
    //
    return ptr_thread;
}
