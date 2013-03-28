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

#include "dotplotinfopropertywidget.h"
#include <QFormLayout>
#include <QtGui>
DotPlotInfoPropertyWidget::DotPlotInfoPropertyWidget(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("Information");
    setWindowIcon(QIcon(":edit.png"));

    mXAverageLabel = new QLabel;
    mYAverageLabel = new QLabel;

    mXVarianceLabel = new QLabel;
    mYVarianceLabel = new QLabel;

    mXSdLabel = new QLabel;
    mYSdLabel = new QLabel;

    mXCvLabel = new QLabel;
    mYCvLabel = new QLabel;

    mXAverageLabel->setToolTip(tr("average"));
    mXVarianceLabel->setToolTip(tr("variance"));
    mXSdLabel->setToolTip(tr("Standard deviation"));
    mXCvLabel->setToolTip(tr("Coeficent of variation"));

    mYAverageLabel->setToolTip(tr("average"));
    mYVarianceLabel->setToolTip(tr("variance"));
    mYSdLabel->setToolTip(tr("Standard deviation"));
    mYCvLabel->setToolTip(tr("Coeficent of variation"));

    QFormLayout* layoutX = new QFormLayout;
    QFormLayout*layoutY = new QFormLayout;

    layoutX->addRow("avg", mXAverageLabel);
    layoutX->addRow("var", mXVarianceLabel);
    layoutX->addRow("sd", mXSdLabel);
    layoutX->addRow("cv", mXCvLabel);

    layoutY->addRow("avg", mYAverageLabel);
    layoutY->addRow("var", mYVarianceLabel);
    layoutY->addRow("sd", mYSdLabel);
    layoutY->addRow("cv",mYCvLabel);

    QGroupBox * Xbox = new QGroupBox;
    Xbox->setTitle("X-info");
    Xbox->setLayout(layoutX);
    Xbox->setCheckable(true);

    QGroupBox * Ybox = new QGroupBox;
    Ybox->setTitle("Y-info");
    Ybox->setLayout(layoutY);
    Ybox->setCheckable(true);

    QGridLayout * l = new QGridLayout;
    l->addWidget(Xbox,0,0);
    l->addWidget(Ybox,0,1);

    setLayout(l);


}

void DotPlotInfoPropertyWidget::setAverage(double value, Qt::Axis axis)
{
    if (axis == Qt::XAxis)
        mXAverageLabel->setText(QString::number(value));
    else
        mYAverageLabel->setText(QString::number(value));
}

void DotPlotInfoPropertyWidget::setVariance(double value, Qt::Axis axis)
{

    if (axis == Qt::XAxis)
        mXVarianceLabel->setText(QString::number(value));
    else
        mYVarianceLabel->setText(QString::number(value));
}

void DotPlotInfoPropertyWidget::setStandardDeviation(double value, Qt::Axis axis)
{
    if (axis == Qt::XAxis)
        mXSdLabel->setText(QString::number(value));
    else
        mYSdLabel->setText(QString::number(value));
}

void DotPlotInfoPropertyWidget::setCv(double value, Qt::Axis axis)
{
    if (axis == Qt::XAxis)
        mXCvLabel->setText(QString::number(value));
    else
        mYCvLabel->setText(QString::number(value));

}
