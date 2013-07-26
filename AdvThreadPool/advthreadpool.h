#ifndef ADVTHREADPOOL_H
#define ADVTHREADPOOL_H
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
#include <QObject>
#include <QThread>
#include <QMap>
#include <QQueue>
#include <QMutex>
//
#include "advthreadjob.h"


QT_FORWARD_DECLARE_CLASS(AdvThread)

class AdvThreadPool : public QObject
{
    Q_OBJECT
    /*
        set threadpool mode of the work
        en_FIFO - First In - First Out. (default mode)
        en_PRIO - the order execution depends of task priority
    */

public:

    enum PoolMode
    {
        en_FIFO,
        en_PRIO
    };

public:

    ~AdvThreadPool();
    //
    static AdvThreadPool&   getInstance     ();
    void                    init            (unsigned int ui_threads_amount = 0);
    bool                    execute         (AdvThreadJob* ptr_job);
    void                    stop            ();
    bool                    isIdle          ();
    void                    setMode         (PoolMode en_mode);
    //
private:
                            AdvThreadPool   (QObject *parent = 0);
    void                    operator=(AdvThreadPool const&);

signals:

public slots:

private slots:
    void            onStandardFinish        ();
    void            onCheckFinish           ();

private:
    //
    AdvThread*      getAvailableThread      ();
    //
    AdvThread*      createReservedThread    ();
    //QThread*        reserveAvailableThread  ();
    //QThread*        createReservedThread    ();
    //
    int             getTaskQueueSize        () const;
    void            addJobToQueue           (AdvThreadJob* ptr_job);
    AdvThreadJob*   extractNextJob          ();

private:
    //typedef QMap<unsigned int, AdvThread*>  ThreadMap;
    typedef QMap<unsigned int, AdvThread*>  ThreadMap;

    mutable QMutex                  m_TaskLocker;
    QQueue<AdvThreadJob*>           m_TaskQueue;
    //
    QMutex                          m_PoolLocker;
    ThreadMap                       m_Pool;
    //
    unsigned int                    m_uiMaxThreadNumber;
    unsigned int                    m_uiUniquer;
    bool                            m_EnableWork;
    PoolMode                        m_enPoolMode;

};

#endif // ADVTHREADPOOL_H
