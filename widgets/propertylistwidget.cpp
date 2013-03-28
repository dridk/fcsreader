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

#include "propertylistwidget.h"
#include <QtGui>
#include <QDebug>
PropertyListWidget::PropertyListWidget(QWidget *parent) :
    QScrollArea(parent)
{

    mContent = new QWidget;
    mContentLayout = new QVBoxLayout;
    mContentLayout->setContentsMargins(0,0,0,0);
    mContentLayout->setSpacing(0);
    mContentLayout->addStretch();
    mContent->setLayout(mContentLayout);
    setWidgetResizable(true);
    setWidget(mContent);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

void PropertyListWidget::addWidget(QWidget *widget)
{

    PropertyWidgetContainer * container = new PropertyWidgetContainer;
    container->setWidget(widget);
    mContentLayout->insertWidget(0,container);


    mContent = new QWidget;
    mContent->setLayout(mContentLayout);


    setWidget(mContent);


}
