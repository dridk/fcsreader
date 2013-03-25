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

#include "gatetreemodel.h"
#include <QObject>
GateTreeModel::GateTreeModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    mRootItem = new Gate;
    mRootItem->setName("root");
}

GateTreeModel::~GateTreeModel()
{
    delete mRootItem;
}

QModelIndex GateTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row,column,parent))
        return QModelIndex();

    Gate * parentItem;
    if (!parent.isValid())
        parentItem = mRootItem;
    else
        parentItem = static_cast<Gate*>(parent.internalPointer());

    Gate * item = qobject_cast<Gate*>(parentItem->children().at(row));
    if ( item)
        return createIndex(row,column,item);
    else
        return QModelIndex();



}

QVariant GateTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    Gate *item = static_cast<Gate*>(index.internalPointer());

    return item->name();

}

int GateTreeModel::rowCount(const QModelIndex &parent) const
{
    if ( parent.column() > 0)
        return 0;

    Gate * parentItem;
    if (!parent.isValid())
        parentItem = mRootItem;
    else
        parentItem = static_cast<Gate*>(parent.internalPointer());

    return parentItem->children().count();



}

int GateTreeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QModelIndex GateTreeModel::parent(const QModelIndex &child) const
{

    if (!child.isValid())
        return QModelIndex();

    Gate * item = static_cast<Gate*>(child.internalPointer());
    Gate * parentItem = qobject_cast<Gate*>(item->parent());

    if (parentItem == mRootItem)
        return QModelIndex();

    return createIndex(parentItem->parent()->children().indexOf(parentItem),0, parentItem);




}

void GateTreeModel::setGate(Gate *gate)
{
    qDeleteAll (mRootItem->children());
    mRootItem->appendChild(gate);
    reset();
}

