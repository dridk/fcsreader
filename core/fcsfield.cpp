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

#include "fcsfield.h"

FcsField::FcsField():
    mName("not defined"),mLabel("not defined"),
    mBitNumber(16),mGain(0),mRange(0),mVoltage(0)
{
}

const QString &FcsField::name() const
{
    return mName;
}

void FcsField::setName(const QString &name)
{
    mName = name;
}

const QString &FcsField::label() const
{
    return mLabel;
}

void FcsField::setLabel(const QString &label)
{
    mLabel = label;
}

int FcsField::bitNumber() const
{
    return mBitNumber;
}

void FcsField::setBitNumber(int bit)
{
    mBitNumber = bit;
}

double FcsField::gain() const
{
    return mGain;
}

void FcsField::setGain(double gain)
{
    mGain = gain;
}

double FcsField::range() const
{
    return mRange;
}

void FcsField::setRange(double range)
{
    mRange = range;
}

int FcsField::voltage() const
{
    return mVoltage;
}

void FcsField::setVoltage(int voltage)
{
    mVoltage = voltage;
}
