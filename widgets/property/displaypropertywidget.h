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

#ifndef COMMONPLOTPROPERTYWIDGET_H
#define COMMONPLOTPROPERTYWIDGET_H

#include <QWidget>
#include "scatterstylecombobox.h"
#include "colorbutton.h"
class DisplayPropertyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayPropertyWidget(QWidget *parent = 0);
    ~DisplayPropertyWidget();

signals:
    void penChanged(const QPen& color);
    void brushChanged(const QBrush& color);
    
private:
    ScatterStyleComboBox * mScatterCombo;
    ColorButton * mPenColor;
    ColorButton * mBrushColor;

    QPen mPen;
    QBrush mBrush;

    
};

#endif // COMMONPLOTPROPERTYWIDGET_H
