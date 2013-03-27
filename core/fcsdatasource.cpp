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

#include "fcsdatasource.h"

FcsDataSource::FcsDataSource()
{
}


double FcsDataSource::value(int row, int column)
{
     Q_ASSERT_X(column<columnCount(), "","column out of range");
    int offset = columnCount() * row + column;
    return mDatas.at(offset);
}

int FcsDataSource::columnCount() const
{
    return mFields.count();
}

int FcsDataSource::rowCount() const
{
    Q_ASSERT_X(mFields.count(), "","no field, divised par 0");
    return mDatas.size() / mFields.count();
}

const FcsField &FcsDataSource::field(int column) const
{
    return mFields.at(column);
}

const QList<FcsField> &FcsDataSource::fields() const
{
    return mFields;
}

void FcsDataSource::setData(const QList<FcsField> &fields, const QVector<double> &datas)
{
    mFields = fields;
    mDatas = datas;


}






