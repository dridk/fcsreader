#include "fcsmodel.h"
#include <QDebug>
FcsModel::FcsModel( QObject *parent):
    QAbstractTableModel(parent)
{
    mGateList = NULL;
    mCurrentGate = "all";

}
int FcsModel::rowCount(const QModelIndex &parent) const
{
    if (!mGateList)
        return 0;

    int row = mGateList->value(mCurrentGate).rowCount();
    return row;
}

int FcsModel::columnCount(const QModelIndex &parent) const
{
    if (!mGateList)
        return 0;
    int col = mGateList->value(mCurrentGate).columnCount();
    return col;
}

QVariant FcsModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();

    if (!mGateList->value(mCurrentGate).rowCount() )
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        if (!mGateList)
            return QVariant();
        return mGateList->value(mCurrentGate).valueAtCoord(index.row(),index.column());
    }
    return QVariant();

}

QVariant FcsModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (!mGateList->value(mCurrentGate).rowCount() )
        return QVariant();


    if (orientation == Qt::Horizontal)
    {
        if ( role == Qt::DisplayRole)
             return mGateList->value(mCurrentGate).headerName(section);


    }

    if (orientation == Qt::Vertical)
    {

        if (role == Qt::DisplayRole)
            return section;
    }



    return QVariant();
}

void FcsModel::setGateList(GateList *gateList)
{
    mGateList = gateList;
    reset();
}



void FcsModel::update()
{
    reset();
}

void FcsModel::setCurrentGate(const QString &key)
{
    mCurrentGate = key;
    reset();


}

