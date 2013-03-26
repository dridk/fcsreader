#include "abstractplotwidget.h"
#include <QDebug>
#include <QMenu>
#include <QGraphicsProxyWidget>

AbstractPlotWidget::AbstractPlotWidget(Gate *rootGate, QWidget *parent) :
    QGraphicsView(parent)
{

    mRootGate = rootGate;
    setScene( new QGraphicsScene);
    mPlot  = new QCustomPlot;
    mPlotItem = new QGraphicsProxyWidget;
    mPropertyWidget = new PropertyListWidget;

    mPlotItem->setWidget(mPlot);
    scene()->addItem(mPlotItem);
    mPlot->addGraph();
    setContextMenuPolicy(Qt::ActionsContextMenu);



    setupProperty();

    connect(mGatePropertyWidget,SIGNAL(gateChanged(Gate*)),this,SLOT(setGate(Gate*)));



}

void AbstractPlotWidget::setTitle(const QString &title)
{
    plot()->setTitle(title);
    setWindowTitle(title);
}

const QString &AbstractPlotWidget::title() const
{
    return windowTitle();
}

void AbstractPlotWidget::setGate(Gate *rootGate)
{
    mRootGate = rootGate;
    replot();
}

void AbstractPlotWidget::test()
{

    qDebug()<<"besoin de suppression";

}


Gate *AbstractPlotWidget::rootGate()
{
    if (mRootGate)
    return mRootGate;
    else return NULL;
}



StatsData AbstractPlotWidget::statsData()
{
    StatsData stats;
    stats.append(qMakePair(QString("average"),QVariant("test")));
    return stats;

}


void AbstractPlotWidget::mousePressEvent(QMouseEvent *event)
{

    //    if (test){
    //        qDebug()<<"press";
    //        QPolygonF poly = mPolygonItem->polygon();
    //        poly.append(event->pos());

    //        mPolygonItem->setPolygon(poly);
    //        mPolygonItem->setVisible(true);
    //    }

    QGraphicsView::mousePressEvent(event);



}

void AbstractPlotWidget::mouseDoubleClickEvent(QMouseEvent *event)
{

    //    QGraphicsPolygonItem * item = new QGraphicsPolygonItem;
    //    item->setPolygon(mPolygonItem->polygon());
    //    item->setBrush(QBrush(QColor(255,0,0,50)));
    //    item->setFlag(QGraphicsItem::ItemIsMovable,true);
    //    scene()->addItem(item);
    //    mPolygonItem->setPolygon(QPolygonF());
    //    mPolygonItem->setVisible(false);
    //    test = false;

    QGraphicsView::mouseDoubleClickEvent(event);


}

void AbstractPlotWidget::mouseMoveEvent(QMouseEvent *event)
{

    //        if (mPolygonItem->polygon().size() > 2)
    //        {
    //            QPolygonF poly = mPolygonItem->polygon();
    //            poly[poly.size()-1] = event->pos();

    //            mPolygonItem->setPolygon(poly);
    //        }


    QGraphicsView::mouseMoveEvent(event);

}

void AbstractPlotWidget::resizeEvent(QResizeEvent *event)
{
    scene()->setSceneRect(0,0,event->size().width(), event->size().height());
    mPlotItem->resize(event->size());

}

void AbstractPlotWidget::setupProperty()
{
    mGatePropertyWidget = new GatePropertyWidget(mRootGate);
    mCommonPropertyWidget = new DisplayPropertyWidget;

    propertyListWidget()->addWidget(mGatePropertyWidget);
    propertyListWidget()->addWidget(mCommonPropertyWidget);


}



