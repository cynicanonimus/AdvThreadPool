#ifndef JOBFORTESTS_H
#define JOBFORTESTS_H
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
#include "../AdvThreadPool/advthreadjob.h"

class JobForTests : public AdvThreadJob
{
public:
    explicit JobForTests(int id, int delay);

public:
    //
    bool    exec    ();
    int     getID   () const {return m_id;}

signals:
    
public slots:

private:
    int m_id;
    int m_idelay;
    
};

#endif // JOBFORTESTS_H
