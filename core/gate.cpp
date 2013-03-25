/***************************************************************************
**                                                                        **
**  FcsViewer, a simple cytometry data viewer made with Qt4 and           **
**  customplot made by Emanuel Eichhammer                                 **
**  Copyright (C) 2013 Sacha Schutz                                       **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author : Sacha Schutz                                        **
**           Website: http://www.labsquare.org                            **
**           Email  : sacha@labsquare.org                                 **
**           Date   : 12.03.12                                            **
****************************************************************************/

#include "gate.h"
#include <QDebug>
Gate::Gate(Gate *parent)
    :QObject(parent),mName("not defined")

{
    setParent(parent);

}

Gate::~Gate()
{
    qDebug()<<"destroy" <<this;
    emit destroyed();
    qDeleteAll(mChilds);

}

const FcsData &Gate::data() const
{
    return mData;
}

void Gate::setData(const FcsData &data)
{
    mData = data;
}

void Gate::appendChild(Gate *child)
{
    child->setParent(this);
    mChilds.append(child);


}
void Gate::removeChild(Gate *child)
{
    mChilds.removeOne(child);
}

QList<Gate *> Gate::allChildren(Gate *parent) const
{
    QList<Gate*> list;
    int i=0;
    foreach ( QObject * obj , parent->children())
    {
        Gate * gate = qobject_cast<Gate*>(obj);
        list.append(gate);
        list.append(allChildren(gate));


    }

    return list;

}



void Gate::setName(const QString &name)
{
    mName = name;
}
const QString &Gate::name() const
{
    return mName;
}



