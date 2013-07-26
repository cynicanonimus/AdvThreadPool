#ifndef ADVTHREAD_H
#define ADVTHREAD_H
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
#include <QThread>
#include <QMutex>
//

QT_FORWARD_DECLARE_CLASS(AdvThreadJob)
//
//


class AdvThread : public QThread
{
    Q_OBJECT
public:
    explicit AdvThread(unsigned int ui_unique_id, QObject *parent = 0);

public:
    //
    void            setJob      (AdvThreadJob* ptr_job);
    void            run         ();
    //
    //void            reserve     ();
    //bool            isIdle      ();
    //bool            isActive    ();
signals:
//    void ThreadStarted(unsigned int ui_unique_id);
    void th_finished();

public slots:

private:
    //
/*
    enum ThreadStatus
    {
        en_RUNNING,
        en_RESERVED,
        en_FINISHED
    };
*/
    //
    //void            setStatus   (ThreadStatus en_status);
    //ThreadStatus    getStatus   ();
    //
    //QMutex          m_StatusLocker;
    //ThreadStatus    m_enStatus;
    //
    AdvThreadJob*   m_ptrActualJob;
    unsigned int    m_ui_UniqueId;
    //
    QMutex          m_RunnerLocker;

    
};

#endif // ADVTHREAD_H
