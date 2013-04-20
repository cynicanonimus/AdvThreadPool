#include "advthread.h"
#include "advthreadjob.h"

AdvThread::AdvThread(unsigned int ui_unique_id, QObject *parent) :
    QThread(parent)
{
    m_ptrActualJob  = NULL;
    m_ui_UniqueId   = ui_unique_id;
    setStatus (en_FINISHED);
}
//
void AdvThread::run()
{
    m_RunnerLocker.lock();
    setStatus (en_RUNNING);
    emit ThreadStarted(m_ui_UniqueId);
    //
    if (NULL != m_ptrActualJob)
    {
        m_ptrActualJob->exec();
        //
        if ( m_ptrActualJob->autoDelete() )
        {
            delete m_ptrActualJob;
        };
        //
        m_ptrActualJob = NULL;
    };
    //
    setStatus (en_FINISHED);
    emit ThreadFinished(m_ui_UniqueId);
    m_RunnerLocker.unlock();
}

void AdvThread::setJob(AdvThreadJob* ptr_job)
{
    m_ptrActualJob = ptr_job;
}

void AdvThread::setStatus   (ThreadStatus en_status)
{
    m_StatusLocker.lock();
    m_enStatus = en_status;
    m_StatusLocker.unlock();
}

AdvThread::ThreadStatus AdvThread::getStatus   ()
{
    ThreadStatus en_status;
    {
        m_StatusLocker.lock();
        en_status = m_enStatus;
        m_StatusLocker.unlock();
    };
    //
    return en_status;
}

bool AdvThread::isIdle   ()
{
    return ( getStatus() == en_FINISHED);
}

bool AdvThread::isActive ()
{
    return ( getStatus() == en_RUNNING);
}

void AdvThread::reserve ()
{
    setStatus(en_RESERVED);
}
