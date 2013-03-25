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

#include "displaypropertywidget.h"
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QtGui>
DisplayPropertyWidget::DisplayPropertyWidget(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("Display");
    setWindowIcon(QIcon(":brush.png"));
    QGridLayout * layout = new QGridLayout;
    mScatterCombo = new ScatterStyleComboBox;
    mPenColor = new ColorButton;
    mBrushColor = new ColorButton;


    QGroupBox * brushBox = new QGroupBox("brush");
    QGroupBox * penBox = new QGroupBox("pen");

    brushBox->setLayout(new QFormLayout);
    brushBox->layout()->addWidget(new QPushButton);

    layout->addWidget(new QLabel("point style"),0,0);
    layout->addWidget(mScatterCombo,0,1);




    setLayout(layout);


}


DisplayPropertyWidget::~DisplayPropertyWidget()
{
    delete mScatterCombo;
}
