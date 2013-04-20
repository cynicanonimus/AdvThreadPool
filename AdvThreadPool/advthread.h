#ifndef ADVTHREAD_H
#define ADVTHREAD_H
//
//
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
    void            reserve     ();
    bool            isIdle      ();
    bool            isActive    ();
signals:
    void ThreadStarted(unsigned int ui_unique_id);
    void ThreadFinished(unsigned int ui_unique_id);

public slots:

private:
    //
    enum ThreadStatus
    {
        en_RUNNING,
        en_RESERVED,
        en_FINISHED
    };
    //
    void            setStatus   (ThreadStatus en_status);
    ThreadStatus    getStatus   ();
    //
    QMutex          m_StatusLocker;
    ThreadStatus    m_enStatus;
    //
    AdvThreadJob*   m_ptrActualJob;
    unsigned int    m_ui_UniqueId;
    //
    QMutex          m_RunnerLocker;

    
};

#endif // ADVTHREAD_H
