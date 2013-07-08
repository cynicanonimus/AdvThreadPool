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
#include "jobfortests.h"
//
#include <QTime>
#include <QCoreApplication>
#include <iostream>

JobForTests::JobForTests(int id, int delay)
{
    m_id = id;
    m_idelay = delay;
}

bool JobForTests::exec()
{
    //
    int i_counter = 0;
    QTime dieTime= QTime::currentTime().addSecs(1);
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        if (i_counter > 5)
            break;
    };
    //
    std::cout<<"job N ["<<m_id<<"]"<<std::endl;
    //
    return true;
}
