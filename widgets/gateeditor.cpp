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

#include "gateeditor.h"
#include <QFormLayout>
#include <QDialogButtonBox>
GateEditor::GateEditor(Gate *gate, QWidget *parent):
    QDialog(parent)
{

    mGate = gate;

    QFormLayout * formLayout = new QFormLayout;
    mColorButton  = new ColorButton;
    mNameEdit = new QLineEdit;
    formLayout->addRow("name", mNameEdit);
    formLayout->addRow("color", mColorButton);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,
                                                       Qt::Horizontal);

    setLayout(new QVBoxLayout);
    QWidget * form = new QWidget;
    form->setLayout(formLayout);
    layout()->addWidget(form);
    layout()->addWidget(buttonBox);


    connect(buttonBox,SIGNAL(rejected()),this,SLOT(reject()));
    connect(buttonBox,SIGNAL(accepted()),this,SLOT(save()));

    mNameEdit->setText(mGate->name());
    mColorButton->setColor(mGate->color());



}

void GateEditor::save()
{
    qDebug()<<"accepted";
    mGate->setName(mNameEdit->text());
    mGate->setColor(mColorButton->color());

   close();
}


