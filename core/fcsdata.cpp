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
    mDataSource = NULL;
}

double FcsData::value(int row, int column) const
{
    return mDataSource->value(mSourceRows.at(row),column);
}

int FcsData::toSourceRow(int row) const
{
    return mSourceRows.at(row);
}


int FcsData::rowCount() const
{
    return mSourceRows.count();
}

int FcsData::columnCount() const
{
    return mDataSource->columnCount();
}

int FcsData::size() const
{
    return mSourceRows.count();
}

const FcsField &FcsData::field(int column) const
{
    return mDataSource->field(column);
}

const QList<FcsField> &FcsData::fields() const
{
    return mDataSource->fields();
}

void FcsData::clear()
{
    mSourceRows.clear();
}

void FcsData::selectAll()
{
    clear();
    for (int i=0; i < mDataSource->rowCount();++i)
        mSourceRows.append(i);

}

void FcsData::select(int sourceRow)
{
    mSourceRows.append(sourceRow);
}

void FcsData::setSource(FcsDataSource *dataSource)
{
    mDataSource = dataSource;


}

/*!
 Statitics : Compute the average from column
*/
double FcsData::average(int column) const
{

    double sum = 0;
    for (int row=0; row<rowCount(); ++row)
        sum += value(row,column);

    return sum/rowCount();
}
/*!
 Statitics : Compute the variance from column
*/
double FcsData::variance(int column) const
{
    double avg = average(column);
    double sum = 0;
    for (int row=0; row<rowCount(); ++row)
    {
        double val = value(row,column);
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



