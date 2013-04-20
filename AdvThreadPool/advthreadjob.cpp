#include "advthreadjob.h"

AdvThreadJob::AdvThreadJob(QObject *parent) :
    QObject(parent)
{
    m_Prio = QThread::IdlePriority;
    m_iRefCounter = 0;
}

AdvThreadJob::~AdvThreadJob()
{

}
