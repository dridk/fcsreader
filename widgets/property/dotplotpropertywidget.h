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

#ifndef DOTPLOTPROPERTYWIDGET_H
#define DOTPLOTPROPERTYWIDGET_H

#include <QWidget>
#include <QtGui>
#include "gate.h"
class DotPlotPropertyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DotPlotPropertyWidget(Gate* rootGate,  QWidget *parent = 0);
    ~DotPlotPropertyWidget();

signals:
    void xFieldChanged(int col);
    void yFieldChanged(int col);
    void xLabelChanged(const QString& label);
    void yLabelChanged(const QString& label);




protected:
    void loadCombo();

private:
    QComboBox * mXFieldComboBox;
    QComboBox * mYFieldComboBox;
    QLineEdit * mXLabel;
    QLineEdit * mYLabel;
    Gate * mRootGate;
    
};

#endif // DOTPLOTPROPERTYWIDGET_H
