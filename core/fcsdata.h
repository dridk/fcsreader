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

#ifndef FCSDATA_H
#define FCSDATA_H
#include <QtCore>
#include "fcsfield.h"
#include "fcsfile.h"
class FcsData;
typedef QMap<QString,FcsData> FcsDataMap;
class FcsData
{
public:
    FcsData();
    double value(int row, int column) const;
    double value(int index) const;
    QVector <double> row(int row) const;
    QVector <double> column(int column)const;
    int rowCount() const;
    int columnCount() const;
    int size() const;
    void selectAll();
    void select(int row);
    void clear();

    //Statistics computation
    double average(int column) const;
    double variance(int column) const;
    double standardDeviation(int column) const;
    double cv(int column) const;

    const QList<FcsField>& fields() const {return mFields;}


private:
    QList<int> mIndex;
    QVector<double> * mDatas;
    QList<FcsField> mFields;
    //enable FcsFile to load data inside
    friend class FcsFile;


};

#endif // FCSDATA_H
