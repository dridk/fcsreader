#include "abstractplotwidget.h"
#include <QDebug>
#include <QMenu>
#include <QGraphicsProxyWidget>

AbstractPlotWidget::AbstractPlotWidget(Gate *gate, QWidget *parent) :
    QGraphicsView(parent)
{

    mGate = gate;
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
    connect(mGate,SIGNAL(changed()),mGatePropertyWidget,SLOT(loadCombo()));


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

void AbstractPlotWidget::setGate(Gate *gate)
{
    mGate = gate;
    connect(mGate,SIGNAL(changed()),this,SIGNAL(gateChanged()));
    emit gateChanged();

}




Gate *AbstractPlotWidget::gate()
{
    if (mGate)
    return mGate;
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

  foreach (QGraphicsItem * item, scene()->items())
  {
      if (item != mPlotItem)
      {

      }

  }


//   fitInView(mPlotItem);
  QGraphicsView::resizeEvent(event);

}

void AbstractPlotWidget::setupProperty()
{
    mGatePropertyWidget = new GatePropertyWidget(gate());
    mCommonPropertyWidget = new DisplayPropertyWidget;

    propertyListWidget()->addWidget(mGatePropertyWidget);
    propertyListWidget()->addWidget(mCommonPropertyWidget);


}



