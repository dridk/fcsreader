#include "gateitem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
GateItem::GateItem(QGraphicsItem *parent)
    :QAbstractGraphicsShapeItem(parent)
{

    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    mPolygon = QPolygonF(QRectF(0,0,50,50));
      mResize = false;
      mPointIndex = 0;

}

void GateItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{


    painter->setBrush(brush());
    painter->setPen(pen());

    painter->drawPolygon(mPolygon);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::red);
    painter->setPen(pen);
    painter->setBrush(QBrush(Qt::red));
    foreach (QPointF p, mPolygon){
        // painter->drawPoint(p);

        QRectF zone(p - QPointF(3,3) ,p + QPointF(3,3));

        painter->drawRect(zone);

    }


   painter->drawPoints(mPoints);

}

QRectF GateItem::boundingRect() const
{

    return mPolygon.boundingRect().adjusted(-10,-10,10,10);

}

void GateItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<event->pos();
    for (int i=0; i<mPolygon.size(); ++i)
    {
        QRectF zone(mPolygon.at(i) - QPointF(3,3) ,mPolygon.at(i) + QPointF(3,3));

        if (zone.contains(event->pos()))
        {
            mPointIndex = i;
            mResize = true;
        }

    }

    return QAbstractGraphicsShapeItem::mousePressEvent(event);
}

void GateItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (mResize){
    mResize = false;
    }
    else
    return QAbstractGraphicsShapeItem::mouseReleaseEvent(event);
}

void GateItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (mResize)
    {
        mPolygon[mPointIndex] = event->pos();
        update();


    }

else
        return QAbstractGraphicsShapeItem::mouseMoveEvent(event);
}

QPolygonF GateItem::mapPolygonToScene() const
{

    QPolygonF newPolygon;


    foreach (QPointF p, polygon())
    {
        newPolygon.append(mapToScene(p));

    }

    return newPolygon;


}
