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

#ifndef FCSFIELD_H
#define FCSFIELD_H
#include <QtCore>
class FcsField
{
public:
    FcsField();
    const QString& name() const;
    void setName(const QString& name);

    const QString& label() const;
    void setLabel(const QString& label);

    int bitNumber() const;
    void setBitNumber(int bit);

    double gain() const;
    void setGain(double gain);

    double range() const;
    void setRange(double range);

    int voltage() const;
    void setVoltage(int voltage);



private:
    QString mName;
    QString mLabel;
    int mBitNumber;
    double mGain;
    double mRange;
    int mVoltage;

};

#endif // FCSFIELD_H
