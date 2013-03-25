#ifndef FCSFILE_H
#define FCSFILE_H

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
#include <QFile>
#include <QHash>
#include <QString>
#include <QVariantMap>
#include <QtCore>
#include "fcsdata.h"

/*!
  Load and read data from a FCS file version 3.0
*/
class FcsFile;
class FcsData;
class FcsFile : public QFile
{
public:
    FcsFile(const QString& fileName, QObject * parent = 0);
    FcsFile(QObject * parent = 0);

    //open file as binary mode
    bool open();

    //Return textSegment
    const QVariantMap& textSegment() const ;

    //Return return dataSegment
    QVector<double> dataSegment() const;

    //Return a copy a data
    FcsData data() ;

    //Return FCS file version
    QString version();

    //TextSegment getter
    int parameterCount() const;
    int eventCount() const ;
    QDateTime aquisitionDate() const ;


protected:
    int textBeginOffset() ;
    int textEndOffset();
    int dataBeginOffset();
    int dataEndOffset();

    void loadTextSegment();
    void loadDataSegment();

private:
    QVariantMap mTextSegment;
    QVector<double> mDataSegment;





};

#endif // FCSFILE_H
