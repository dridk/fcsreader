#include "fcsdata.h"
#include <QDebug>
FcsData::FcsData()
{
    mRowCount = 0;
    mColumnCount = 0;
    mSource = 0;
}

double FcsData::value(int row, int column) const
{
    if (!mSource)
        return -1;
    return mSource->at(mIds.value(mColumnCount * row + column));
}


void FcsData::setRowCount(int count)
{
    mRowCount = count;
}

void FcsData::setColumnCount(int count)
{
    mColumnCount = count;



}

int FcsData::rowCount() const
{
    return mRowCount;
}

int FcsData::columnCount() const
{
    return mColumnCount;
}

int FcsData::size() const
{
    return mIds.size();
}

void FcsData::fill()
{
    if (!mSource)
        return;
    mIds.clear();
    for (int i=0; i<mSource->size(); ++i)
        mIds.append(i);
}

const QString &FcsData::headerName(int column) const
{
    return mHeaders.value(column,"not defined");
}

void FcsData::setHeaderName(int column, const QString &name)
{
    mHeaders[column] = name;
}

void FcsData::setSource(QVector<double> *source)
{
    mSource = source;


}
