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

DotPlotWidget::DotPlotWidget(Gate *rootGate, QWidget *parent):
    AbstractPlotWidget(rootGate,parent)

{
    mXField = 0;
    mYField = 1;
    mPropertyWidget = new DotPlotPropertyWidget(rootGate);
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


    connect(gateAction,SIGNAL(triggered(bool)),this,SLOT(setGateEditing(bool)));
    connect(mPropertyWidget,SIGNAL(xFieldChanged(int)),this,SLOT(setXField(int)));
    connect(mPropertyWidget,SIGNAL(yFieldChanged(int)),this,SLOT(setYField(int)));

    connect(mPropertyWidget,SIGNAL(xFieldChanged(int)),this,SLOT(setXLabel()));
    connect(mPropertyWidget,SIGNAL(yFieldChanged(int)),this,SLOT(setYLabel()));


    connect(mPropertyWidget,SIGNAL(xLabelChanged(QString)),this,SLOT(setXLabel(QString)));
    connect(mPropertyWidget,SIGNAL(yLabelChanged(QString)),this,SLOT(setYLabel(QString)));



    ShapeItem * item = new ShapeItem;
    scene()->addItem(item);

    scene()->addItem(mGateEditItem);
    mGateEditItem->setVisible(false);

}

void DotPlotWidget::replot()
{
    QCPDataMap dataMap;
    if (rootGate() == NULL)
        return;

        for (int i=0; i<rootGate()->data().rowCount(); ++i)
        {
            double x = rootGate()->data().value(i,mXField);
            double y = rootGate()->data().value(i,mYField);

            QCPData newsData;
            newsData.key = x;
            newsData.value = y;
            newsData.index = i;

            dataMap.insertMulti(x,newsData);

        }

        plot()->setTitle(QString::number(dataMap.count()));
        plot()->graph()->setData(&dataMap,true);
        plot()->graph()->setPen(QPen(rootGate()->color()));
        //plot()->rescaleAxes();
        plot()->xAxis->setRange(0,1024);
        plot()->yAxis->setRange(0,1024);


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
            rootGate()->appendChild(item->gate());
        }

        //compute data inside the shape
        QPolygonF poly = item->mapToScene(item->polygon());
        QList<int> events;
        foreach ( QCPData data, plot()->graph()->data()->values())
        {
            double x  = plot()->xAxis->coordToPixel(data.key);
            double y  = plot()->yAxis->coordToPixel(data.value);

            if (poly.containsPoint( QPointF(x,y),Qt::WindingFill))
                events.append(data.index);

        }

        qDebug()<<events.count()<<"trouvé";
        FcsData newData = rootGate()->data();
        newData.setRows(events);
        item->gate()->setData(newData);


    }




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
            delete item;
        }
    }

}









