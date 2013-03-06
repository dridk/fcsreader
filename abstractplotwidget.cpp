#include "abstractplotwidget.h"
#include <QDebug>
#include <QMenu>
AbstractPlotWidget::AbstractPlotWidget(QWidget *parent) :
    QCustomPlot(parent)
{

 QAction * rescaleAction = new QAction("rescale",this);
  addAction(rescaleAction);
 connect(rescaleAction,SIGNAL(triggered()),this,SLOT(rescaleAxes()));


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

    QCustomPlot::mousePressEvent(event);



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

    QCustomPlot::mouseDoubleClickEvent(event);


}

void AbstractPlotWidget::mouseMoveEvent(QMouseEvent *event)
{

//        if (mPolygonItem->polygon().size() > 2)
//        {
//            QPolygonF poly = mPolygonItem->polygon();
//            poly[poly.size()-1] = event->pos();

//            mPolygonItem->setPolygon(poly);
//        }


        QCustomPlot::mouseMoveEvent(event);

}

