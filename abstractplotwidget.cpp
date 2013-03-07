#include "abstractplotwidget.h"
#include <QDebug>
#include <QMenu>
#include <QGraphicsProxyWidget>
AbstractPlotWidget::AbstractPlotWidget(QWidget *parent) :
    QGraphicsView(parent)
{

    setScene( new QGraphicsScene);
    mPlot  = new QCustomPlot;
    mPlotItem = new QGraphicsProxyWidget;
    mPlotItem->setWidget(mPlot);
    scene()->addItem(mPlotItem);
    mPlot->addGraph();




}

void AbstractPlotWidget::setFcsData(const FcsData &fcsData)
{
    mFcsData = fcsData;

}

const FcsData &AbstractPlotWidget::fcsData() const
{
    return mFcsData;
}

void AbstractPlotWidget::contextMenuEvent(QContextMenuEvent * event)
{

    //    QMenu *menu=new QMenu;

    //    menu->addAction("test");
    //         menu->exec(event->globalPos());



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

