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

#include "fcsdata.h"
#include <cmath>
FcsData::FcsData()
{
    mDatas = NULL;
}
/*!
  Returns data value from row and colum
*/
double FcsData::value(int row, int column) const
{
    int dataIndex = mIndexes.at(columnCount() * row + column);
    return mDatas->value(dataIndex, -1);
}

double FcsData::value(int index) const
{
    return mDatas->value(mIndexes.at(index));
}

/*!
  Returns all data of a specific row
*/
QVector<double> FcsData::row(int row) const
{
    QVector <double> data;
    for (int i=row*columnCount(); i<row*columnCount()+columnCount(); ++i)
        data.append(value(i));

    return data;
}
/*!
  Returns all data of a specific column
*/
QVector<double> FcsData::column(int column) const
{
    QVector <double> data;
    for (int index = column ; index < mIndexes.size(); index+=columnCount())
    {
        data.append(value(index));
    }

    return data;
}
/*!
  Returns row count of data
*/
int FcsData::rowCount() const
{
    Q_ASSERT_X(columnCount() != 0, "", "division by zero");
    return mIndexes.size()/columnCount();
}
/*!
  Returns column count of data
*/
int FcsData::columnCount() const
{
    return mFields.size();
}
/*!
  Returns total count of value
*/
int FcsData::size() const
{
    Q_ASSERT_X(columnCount() != 0, "", "division by zero");
    return mIndexes.size();
}
/*!
 Select all data from Fcs file
*/
void FcsData::selectAll()
{
    mIndexes.clear();
    for (int i=0; i<mDatas->size(); ++i)
        mIndexes.append(i);
}
/*!
 Select data at row from Fcs file
*/
void FcsData::select(int row)
{
    for (int i=row * columnCount(); i< row*columnCount() + columnCount(); ++i)
        mIndexes.append(i);
}
/*!
 Unselect all data from fcs file
*/
void FcsData::clear()
{
    mIndexes.clear();
}
/*!
 Statitics : Compute the average from column
*/
double FcsData::average(int column) const
{

    double sum = 0;
    for (int index = column ; index < size(); index+=columnCount())
        sum += value(index);

    return sum/rowCount();
}
/*!
 Statitics : Compute the variance from column
*/
double FcsData::variance(int column) const
{
    double avg = average(column);
    double sum = 0;
    for (int index = column ; index < size(); index+=columnCount())
    {
        double val = value(index);
        sum += (val - avg) *(val - avg) ;

    }
    return sum/rowCount();
}
/*!
 Statitics : Compute the standard deviation from column
*/
double FcsData::standardDeviation(int column) const
{
    return sqrt(variance(column));
}
/*!
 Statitics : Compute the coeficient of variation from column
*/
double FcsData::cv(int column) const
{
    return standardDeviation(column) / average(column);
}

//This functions write indexes , using to create sub gate Data
void FcsData::setRows(const QList<int> &rows)
{
    mIndexes.clear();
    foreach ( int row , rows)
    {
        for (int i=columnCount() * row; i<columnCount() * row + columnCount(); ++i){
            mIndexes.append(i);
        }
    }

}


