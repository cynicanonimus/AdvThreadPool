#ifndef JOBFORTESTS_H
#define JOBFORTESTS_H

#include <QObject>
#include "../AdvThreadPool/advthreadjob.h"

class JobForTests : public AdvThreadJob
{
    Q_OBJECT
public:
    explicit JobForTests(int id, int delay, QObject *parent = 0);

public:
    //
    bool    exec();
    int     getID() const {return m_id;}


signals:
    
public slots:

private:
    int m_id;
    int m_idelay;
    
};

#endif // JOBFORTESTS_H
