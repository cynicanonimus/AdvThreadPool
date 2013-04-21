#ifndef ADVTHREADJOB_H
#define ADVTHREADJOB_H
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
#include <QRunnable>

class AdvThreadJob
{

public:
    explicit AdvThreadJob();
    virtual ~AdvThreadJob();

public:
    bool                autoDelete     ()                  const    { return m_iRefCounter != -1; }
    void                setAutoDelete  ( bool _autoDelete)          { m_iRefCounter = _autoDelete ? 0 : -1; }
    //
    void                setPriority    ( QThread::Priority en_prio);
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
