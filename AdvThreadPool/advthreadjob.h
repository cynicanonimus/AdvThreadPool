#ifndef ADVTHREADJOB_H
#define ADVTHREADJOB_H

#include <QObject>
#include <QThread>
#include <QRunnable>

class AdvThreadJob : public QObject
{
    Q_OBJECT
public:
    explicit AdvThreadJob(QObject *parent = 0);
    virtual ~AdvThreadJob();

public:
    bool                autoDelete     ()                  const    { return m_iRefCounter != -1; }
    void                setAutoDelete  ( bool _autoDelete)          { m_iRefCounter = _autoDelete ? 0 : -1; }
    //
    void                setPriority    ( QThread::Priority en_prio) { m_Prio = en_prio; }
    QThread::Priority   getPriority    () const                     { return m_Prio;}
    //
    virtual bool        exec() = 0;

signals:
    
public slots:

private:
    int                     m_iRefCounter;
    QThread::Priority       m_Prio;
};

#endif // ADVTHREADJOB_H
