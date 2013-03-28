#include "dotplotwidget.h"
#include <QDebug>
#include <QMatrix>
#include <QGraphicsProxyWidget>
#include <QAction>
#include "qcustomplot.h"
#include <QContextMenuEvent>
#include <QMenu>
#include <QCursor>
#include <QUuid>
#include "shapeitem.h"
#include "dotplotpropertywidget.h"

DotPlotWidget::DotPlotWidget(Gate *gate, QWidget *parent):
    AbstractPlotWidget(gate,parent)

{
    mXField = 0;
    mYField = 1;
    mPropertyWidget = new DotPlotPropertyWidget(gate);
    mInfoWidget = new DotPlotInfoPropertyWidget;
    mGateEditItem = new QGraphicsPolygonItem;
    plot()->graph()->setPen(QPen(Qt::black));
    plot()->xAxis->setRange(0,1024);
    plot()->yAxis->setRange(0,1024);
    plot()->graph()->setLineStyle(QCPGraph::lsNone);
    plot()->graph()->setScatterStyle(QCP::ssDot);
    plot()->setRangeZoom(Qt::Horizontal | Qt::Vertical);


    QAction * gateAction = new QAction(QIcon(":radar_plot-26"), "Add gate",this);
    gateAction->setCheckable(true);

    addAction(gateAction);

    setWindowTitle("plot");
    setYLabel();
    setXLabel();

    propertyListWidget()->addWidget(mPropertyWidget);
    propertyListWidget()->addWidget(mInfoWidget);


    connect(gateAction,SIGNAL(triggered(bool)),this,SLOT(setGateEditing(bool)));
    connect(mPropertyWidget,SIGNAL(xFieldChanged(int)),this,SLOT(setXField(int)));
    connect(mPropertyWidget,SIGNAL(yFieldChanged(int)),this,SLOT(setYField(int)));

    connect(mPropertyWidget,SIGNAL(xFieldChanged(int)),this,SLOT(setXLabel()));
    connect(mPropertyWidget,SIGNAL(yFieldChanged(int)),this,SLOT(setYLabel()));


    connect(mPropertyWidget,SIGNAL(xLabelChanged(QString)),this,SLOT(setXLabel(QString)));
    connect(mPropertyWidget,SIGNAL(yLabelChanged(QString)),this,SLOT(setYLabel(QString)));

    connect(this,SIGNAL(gateChanged()),this,SLOT(replot()));
    connect(this,SIGNAL(gateChanged()),this,SLOT(allSubGateChanged()));


    scene()->addItem(mGateEditItem);
    mGateEditItem->setVisible(false);

}

void DotPlotWidget::replot()
{
    QCPDataMap dataMap;
    if (gate() == NULL)
        return;

    qDebug()<<"replot";


    for (int i=0; i<gate()->data().rowCount(); ++i)
    {
        double x = gate()->data().value(i,mXField);
        double y =gate()->data().value(i,mYField);

        QCPData newsData;
        newsData.key = x;
        newsData.value = y;
        newsData.index = gate()->data().toSourceRow(i);

        dataMap.insertMulti(x,newsData);

    }

    plot()->setTitle(QString::number(dataMap.count()));
    plot()->graph()->setData(&dataMap,true);
    plot()->graph()->setPen(QPen(gate()->color()));
    //plot()->rescaleAxes();
    plot()->xAxis->setRange(0,1024);
    plot()->yAxis->setRange(0,1024);
    plot()->replot();


    //Set info
    mInfoWidget->setAverage(gate()->data().average(mXField),Qt::XAxis);
    mInfoWidget->setVariance(gate()->data().variance(mXField),Qt::XAxis);
    mInfoWidget->setCv(gate()->data().cv(mXField),Qt::XAxis);
    mInfoWidget->setStandardDeviation(gate()->data().standardDeviation(mXField),Qt::XAxis);

    mInfoWidget->setAverage(gate()->data().average(mYField),Qt::YAxis);
    mInfoWidget->setVariance(gate()->data().variance(mYField),Qt::YAxis);
    mInfoWidget->setCv(gate()->data().cv(mYField),Qt::YAxis);
    mInfoWidget->setStandardDeviation(gate()->data().standardDeviation(mYField),Qt::YAxis);



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
        plot()->xAxis->setLabel(gate()->data().fields().at(mXField).name());
    else
        plot()->xAxis->setLabel(label);

    plot()->replot();
}

void DotPlotWidget::setYLabel(const QString &label)
{
    //if user label is empty, use the fcs data filed name
    if (label.isEmpty())
        plot()->yAxis->setLabel(gate()->data().fields().at(mYField).name());
    else
        plot()->yAxis->setLabel(label);

    plot()->replot();
}

void DotPlotWidget::setGateEditing(bool editing)
{

    mGateEditItem->setVisible(editing);



}

void DotPlotWidget::computeGate()
{
    ShapeItem * item = qobject_cast<ShapeItem*>(sender());
    if (item->metaObject()->className() ==QString("ShapeItem"))
    {
        //Create a new gate if none are associated with the shapeItem
        if (!item->gate())
        {
            item->setGate(new Gate);
            item->gate()->setName(QUuid::createUuid().toString());
            gate()->appendChild(item->gate());


        }

        //compute data inside the shape
        QPolygonF poly = item->mapToScene(item->polygon());
        FcsData newData = gate()->data();
        newData.clear();

        foreach ( QCPData data, plot()->graph()->data()->values())
        {
            double x  = plot()->xAxis->coordToPixel(data.key);
            double y  = plot()->yAxis->coordToPixel(data.value);

            if (poly.containsPoint( QPointF(x,y),Qt::WindingFill))
                newData.select(data.index);


        }


        item->gate()->setData(newData);


    }




}

void DotPlotWidget::allSubGateChanged()
{
    foreach (ShapeItem * item, mShapeItems)
         item->change();

}

void DotPlotWidget::mousePressEvent(QMouseEvent *event)
{

    if (mGateEditItem->isVisible())
    {
        scene()->clearSelection();
        QPolygon poly = mGateEditItem->polygon().toPolygon();
        poly.append(event->pos());
        mGateEditItem->setPolygon(poly);

    }

    else AbstractPlotWidget::mousePressEvent(event);


}

void DotPlotWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (mGateEditItem->isVisible())
    {

        QPolygon poly = mGateEditItem->polygon().toPolygon();
        if (poly.count() == 1)
            poly.append(event->pos());

        if ( poly.count() > 0)
        {
            poly[poly.count()-1] = event->pos();
            mGateEditItem->setPolygon(poly);
        }
    }

    else AbstractPlotWidget::mouseMoveEvent(event);

}

void DotPlotWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (mGateEditItem->isVisible())
    {
        ShapeItem * item = new ShapeItem();
        connect(item,SIGNAL(changed()),this,SLOT(computeGate()));
        mShapeItems.append(item);
        item->setPolygon(mGateEditItem->polygon().toPolygon());
        mGateEditItem->setVisible(false);

        actions().at(0)->setChecked(false);
        mGateEditItem->setPolygon(QPolygonF());
        item->setSelected(true);
        scene()->addItem(item);

    }

    else AbstractPlotWidget::mouseDoubleClickEvent(event);

}

void DotPlotWidget::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_Delete)
    {
        qDebug()<<"delete items"<<scene()->selectedItems().count();
        foreach (QGraphicsItem * item, scene()->selectedItems())
        {
            mShapeItems.removeOne((ShapeItem*)(item));
            delete item;
        }
    }

}









