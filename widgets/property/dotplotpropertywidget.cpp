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

#include "dotplotpropertywidget.h"
#include <QFormLayout>
#include <QLocale>
DotPlotPropertyWidget::DotPlotPropertyWidget(Gate *rootGate, QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("Data");
    setWindowIcon(QIcon(":edit.png"));

    mRootGate = rootGate;
    mXFieldComboBox = new QComboBox;
    mYFieldComboBox = new QComboBox;
    mXLabel = new QLineEdit;
    mYLabel = new QLineEdit;

    QFormLayout * layout = new QFormLayout;

    layout->addRow(tr("X-Data"), mXFieldComboBox);
    layout->addRow(tr("Y-Data"), mYFieldComboBox);
    layout->addRow(tr("X-Label"), mXLabel);
    layout->addRow(tr("Y-Label"), mYLabel);

    setLayout(layout);
    loadCombo();

    connect(mXFieldComboBox,SIGNAL(currentIndexChanged(int)),this,SIGNAL(xFieldChanged(int)));
    connect(mYFieldComboBox,SIGNAL(currentIndexChanged(int)),this,SIGNAL(yFieldChanged(int)));

    connect(mXLabel,SIGNAL(textEdited(QString)),this,SIGNAL(xLabelChanged(QString)));
    connect(mYLabel,SIGNAL(textEdited(QString)),this,SIGNAL(yLabelChanged(QString)));


}

DotPlotPropertyWidget::~DotPlotPropertyWidget()
{
    delete mXFieldComboBox;
    delete mYFieldComboBox;

}

void DotPlotPropertyWidget::loadCombo()
{


    foreach (FcsField field, mRootGate->data().fields())
    {
        mXFieldComboBox->addItem(field.name());
        mYFieldComboBox->addItem(field.name());
    }







}
