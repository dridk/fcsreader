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

#include "shapeitem.h"
#include <QPainter>
#include <QDebug>
ShapeItem::ShapeItem( QGraphicsItem * parent ):
    QGraphicsItem(parent)
{
    mIsEditing = false;
    mEditingPointIndex = 0;
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);

    mPolygon = QPolygon(QRect(0,0,50,50));

    QTransform transform;
    transform.rotate(45);
    mPolygon = transform.map(mPolygon);

}

void ShapeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QPen pen;
    pen.setStyle(Qt::DashLine);
    pen.setColor(Qt::lightGray);
    painter->setPen(pen);
    painter->drawRect(mPolygon.boundingRect());

    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::black);
    pen.setWidth(5);
    painter->setPen(pen);

    painter->drawPoint(mPolygon.boundingRect().bottomRight());


    painter->setPen(QPen(Qt::red));
    painter->drawPolygon(mPolygon);
}

QRectF ShapeItem::boundingRect() const
{

    return mPolygon.boundingRect().adjusted(-20,-20,20,20);
}

void ShapeItem::setMode(ShapeItem::Mode mode)
{
    mCurrentMode = mode;
}

void ShapeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    QRect corner = QRect(mPolygon.boundingRect().bottomRight()-QPoint(5,5),
                         mPolygon.boundingRect().bottomRight()+QPoint(5,5));

    if (corner.contains(event->pos().toPoint()))
    {
        mIsEditing = true;
    }






}

void ShapeItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    setMode(mCurrentMode == ShapeMode ? NodeMode : ShapeMode);
}

void ShapeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    if (mIsEditing)
    {
        qDebug()<<"editing";

        QPoint diff = event->pos().toPoint() - mPolygon.boundingRect().bottomRight();


        QTransform transform;
        qreal sx = qreal(diff.x())/qreal(mPolygon.boundingRect().width()) + 1;
        qreal sy = qreal(diff.y())/qreal(mPolygon.boundingRect().height()) + 1;


        transform.scale(sx,sy);
        mPolygon = transform.map(mPolygon);


        update();

    }


    else
        QGraphicsItem::mouseMoveEvent(event);




}

void ShapeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    mIsEditing= false;
    QGraphicsItem::mouseReleaseEvent(event);
}
