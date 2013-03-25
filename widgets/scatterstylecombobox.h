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

#ifndef SCATTERSTYLECOMBOBOX_H
#define SCATTERSTYLECOMBOBOX_H

#include <QComboBox>
#include "qcustomplot.h"
class ScatterStyleComboBox : public QComboBox
{
    Q_OBJECT
    Q_ENUMS(ScatterStyle)
    Q_PROPERTY (int value READ value WRITE setValue USER true)

public:
    enum ScatterStyle { ssNone       ///< no scatter symbols are drawn (e.g. in QCPGraph, data only represented with lines)
                        ,ssDot       ///< a single pixel
                        ,ssCross     ///< a cross (x)
                        ,ssPlus      ///< a plus (+)
                        ,ssCircle    ///< a circle which is not filled
                        ,ssDisc      ///< a circle which is filled with the color of the pen (not the brush!)
                        ,ssSquare    ///< a square which is not filled
                        ,ssDiamond   ///< a diamond which is not filled
                        ,ssStar      ///< a star with eight arms, i.e. a combination of cross and plus
                        ,ssTriangle  ///< an equilateral triangle which is not filled, standing on baseline
                        ,ssTriangleInverted ///< an equilateral triangle which is not filled, standing on corner
                        ,ssCrossSquare      ///< a square which is not filled, with a cross inside
                        ,ssPlusSquare       ///< a square which is not filled, with a plus inside
                        ,ssCrossCircle      ///< a circle which is not filled, with a cross inside
                        ,ssPlusCircle       ///< a circle which is not filled, with a plus inside
                        ,ssPeace     ///< a circle which is not filled, with one vertical and two downward diagonal lines
//                        ,ssPixmap    ///< a custom pixmap specified by setScatterPixmap, centered on the data point coordinates
                      };
    explicit ScatterStyleComboBox(QWidget *parent = 0);
    
     int value() {return currentIndex();}
    void setValue(int value){
        qDebug()<<"from widget"<<value;
        setCurrentIndex(value);
    }

    
};

#endif // SCATTERSTYLECOMBOBOX_H
