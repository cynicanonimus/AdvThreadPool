#include "advthread.h"
#include "advthreadjob.h"
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
