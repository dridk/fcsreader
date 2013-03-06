#include "fcsmodel.h"
#include <QDebug>
FcsModel::FcsModel(QObject *parent):
    QAbstractTableModel(parent)
{

}
int FcsModel::rowCount(const QModelIndex &parent) const
{
    int row = mFcsData.rowCount();
    return row;
}

int FcsModel::columnCount(const QModelIndex &parent) const
{
    int col = mFcsData.columnCount();
    return col;
}

QVariant FcsModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return mFcsData.value(index.row(),index.column());
    }
    return QVariant();

}

QVariant FcsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {

        return mFcsData.headerName(section);
    }


    return QVariant();
}

void FcsModel::setSource(const FcsData &data)
{
    mFcsData = data;
    reset();
}

void FcsModel::update()
{
    reset();
}

