#include "dotplotwidget.h"
#include <QDebug>
#include <QMatrix>
#include <QGraphicsProxyWidget>
#include <QAction>
#include "qcustomplot.h"
#include <QContextMenuEvent>
#include <QMenu>
#include "shapeitem.h"
#include "dotplotpropertywidget.h"

DotPlotWidget::DotPlotWidget(Gate *rootGate, QWidget *parent):
    AbstractPlotWidget(rootGate,parent)

{
    mXField = 0;
    mYField = 1;
    mPropertyWidget = new DotPlotPropertyWidget(rootGate);

    plot()->graph()->setPen(QPen(Qt::black));
    plot()->xAxis->setRange(0,1024);
    plot()->yAxis->setRange(0,1024);
    plot()->graph()->setLineStyle(QCPGraph::lsNone);
    plot()->graph()->setScatterStyle(QCP::ssDot);
    plot()->setRangeZoom(Qt::Horizontal | Qt::Vertical);



    addAction(new QAction("data source",this));
    addAction(new QAction("Display",this));

    setWindowTitle("plot");
    setYLabel();
    setXLabel();

    propertyListWidget()->addWidget(mPropertyWidget);

   connect(mPropertyWidget,SIGNAL(xFieldChanged(int)),this,SLOT(setXField(int)));
   connect(mPropertyWidget,SIGNAL(yFieldChanged(int)),this,SLOT(setYField(int)));

   connect(mPropertyWidget,SIGNAL(xLabelChanged(QString)),this,SLOT(setXLabel(QString)));
   connect(mPropertyWidget,SIGNAL(yLabelChanged(QString)),this,SLOT(setYLabel(QString)));


   ShapeItem * item = new ShapeItem;
   scene()->addItem(item);

}

void DotPlotWidget::replot()
{
    plot()->graph()->setData(rootGate()->data().column(mXField),
                             rootGate()->data().column(mYField));
    plot()->rescaleAxes();

    plot()->replot();

}

void DotPlotWidget::setXField(int col)
{
    mXField = col;
    replot();

}

void DotPlotWidget::setYField(int col)
{
    mYField = col;
    replot();
}

void DotPlotWidget::setXLabel(const QString &label)
{
    //if user label is empty, use the fcs data filed name
    if (label.isEmpty())
        plot()->xAxis->setLabel(rootGate()->data().fields().at(mXField).name());
    else
     plot()->xAxis->setLabel(label);

   plot()->replot();
}

void DotPlotWidget::setYLabel(const QString &label)
{
    //if user label is empty, use the fcs data filed name
    if (label.isEmpty())
        plot()->yAxis->setLabel(rootGate()->data().fields().at(mYField).name());
    else
     plot()->yAxis->setLabel(label);

  plot()->replot();
}





