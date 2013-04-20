#ifndef ADVTHREADPOOL_H
#define ADVTHREADPOOL_H


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
public:

    ~AdvThreadPool();
    //
    static AdvThreadPool&   getInstance ();
    void                    init        (unsigned int ui_threads_amount = 0);
    bool                    execute     (AdvThreadJob* ptr_job);
    void                    stop        (bool b_wait_until_idle = true);
    bool                    isIdle      ();

private:
    AdvThreadPool(QObject *parent = 0);
    //
    //
             AdvThreadPool (AdvThreadPool const&);
    void operator=(AdvThreadPool const&);


signals:

public slots:
    void onFinishThread(unsigned int);

private slots:

private:
    AdvThread*  reserveAvailableThread  ();
    AdvThread*  createReservedThread    ();
    //
    int             getTaskQueueSize        () const;
    void            addJobToQueue           (AdvThreadJob* ptr_job);
    AdvThreadJob*   extractNextJob          ();

private:
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

};

#endif // ADVTHREADPOOL_H
