#include "fcsdata.h"
#include <QDebug>
FcsData::FcsData()
    :QList<int>()
{
    mRowCount = 0;
    mColumnCount = 0;
    mSource = 0;


}




double FcsData::valueAtCoord(int row, int column) const
{
    return mSource->value(value(mColumnCount * row + column));
}

void FcsData::appendRow(int row)
{
    for (int i=mColumnCount * row; i<mColumnCount * row + mColumnCount; ++i){
        append(i);

    }

    mRowCount++;

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


void FcsData::fill()
{
    if (!mSource)
        return;

    clear();
    for (int i=0; i<mSource->size(); ++i)
        append(i);

    if (mColumnCount > 0)
        mRowCount = int(size() / mColumnCount);
}

QString FcsData::headerName(int column) const
{
    return mHeaders.value(column,"not defined");

}

void FcsData::setHeaderName(int column, const QString &name)
{
    mHeaders[column] = name;
}

void FcsData::setSource( QVector<double> *source)
{
    mSource = source;


}
