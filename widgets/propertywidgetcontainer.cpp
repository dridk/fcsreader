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

#include "propertywidgetcontainer.h"
#include <QtGui>
PropertyWidgetContainer::PropertyWidgetContainer(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout( this );
    layout->setSpacing( 0 );
    layout->setContentsMargins( 0, 0, 0, 0 );
    setLayout( layout );

    QHBoxLayout * headerLayout = new QHBoxLayout;
    QFrame * header = new QFrame;
    header->setFrameShape( QFrame::Panel );
    header->setFrameShadow( QFrame::Raised );

    header->setLayout(headerLayout);
    mToolButton = new QToolButton;
    mTitleLabel = new QLabel("no title");
    mIconLabel = new QLabel;
    mIconLabel->setFixedSize(16,16);
    mToolButton->setArrowType(Qt::DownArrow);
    mToolButton->setCheckable(true);
    mToolButton->setChecked(true);
    headerLayout->addWidget(mIconLabel);
    headerLayout->addWidget(mTitleLabel);
    headerLayout->addWidget(mToolButton);
//    header->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    headerLayout->setContentsMargins(2,0,0,0);

    layout->addWidget(header);

    mContent = new QWidget;
    QVBoxLayout * contentLayout = new QVBoxLayout;
    contentLayout->setContentsMargins(0,0,0,0);
    mContent->setLayout(contentLayout);

    layout->addWidget(mContent);


    connect(mToolButton,SIGNAL(toggled(bool)),this,SLOT(collapse(bool)));


}

void PropertyWidgetContainer::setTitle(const QString &title)
{
    mTitleLabel->setText(title);
}

void PropertyWidgetContainer::setIcon(const QIcon &icon)
{
    mIconLabel->setPixmap(icon.pixmap(16,16));
}

void PropertyWidgetContainer::setWidget(QWidget *widget)
{

    mContent->layout()->addWidget(widget);
    setTitle(widget->windowTitle());
    setIcon(widget->windowIcon());

}

void PropertyWidgetContainer::expand(bool expand)
{
       mContent->setVisible(!expand);
}

void PropertyWidgetContainer::collapse(bool collapse)
{

    mContent->setVisible(collapse);
}
