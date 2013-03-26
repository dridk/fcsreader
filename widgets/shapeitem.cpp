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
#include <QCursor>
#include <QGraphicsScene>
ShapeItem::ShapeItem( QGraphicsItem * parent ):
    QAbstractGraphicsShapeItem(parent)
{
    mIsEditing = false;
    mCurrentPointIndex = 0;
    mCurrentMode = ShapeMode;
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);

    mPolygon.append(QPoint(50,0));
    mPolygon.append(QPoint(0,200));
    mPolygon.append(QPoint(100,100));


    setBrush(QBrush(Qt::red));



}

void ShapeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setRenderHint(QPainter::Antialiasing,true);
    QPolygon poly;
    if (mIsEditing)
        poly = mEditPolygon;
    else
        poly = mPolygon;

    painter->setCompositionMode(QPainter::CompositionMode_Plus);
    painter->setPen(QPen(brush().color().darker()));
    QColor col = brush().color();

    painter->setBrush(QBrush(col));
    painter->drawPolygon(poly);

    painter->setCompositionMode(QPainter::CompositionMode_SourceOver);

    painter->setBrush(QBrush(Qt::transparent));
    painter->setPen(QPen(col.darker()));

    painter->drawPolygon(poly);

    //Draw bounding rect selector
    QPen myPen;
    myPen.setStyle(Qt::DashLine);
    myPen.setColor(Qt::darkGray);

    myPen.setWidth(1);
    painter->setBrush(Qt::transparent);
    painter->setPen(myPen);
    painter->drawRect(poly.boundingRect());

    //define node or resize grip
    myPen.setStyle(Qt::SolidLine);
    myPen.setColor(Qt::black);
    myPen.setWidth(5);
    painter->setPen(myPen);

    if (mode() == ShapeMode)
    {
        //draw grip for resizing
        painter->drawPoint(poly.boundingRect().bottomRight());
    }

    if (mode() == NodeMode)
    {
        //draw nodes
        foreach (QPoint p, poly)
            painter->drawPoint(p);
    }




}

QRectF ShapeItem::boundingRect() const
{
    QPolygon poly;
    if (mIsEditing)
        poly = mEditPolygon;
    else
        poly = mPolygon;
    return poly.boundingRect().adjusted(-20,-20,20,20);
}

void ShapeItem::setMode(ShapeItem::Mode mode)
{
    mCurrentMode = mode;
}

void ShapeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    QList<QPoint> points;

    if (mode() == ShapeMode)
        points.append(mPolygon.boundingRect().bottomRight());

    if (mode() == NodeMode)
        points.append(mPolygon.toList());

    int i = 0;
    foreach ( QPoint p, points)
    {
        QRect node = QRect(p-QPoint(5,5),
                           p+QPoint(5,5));

        if (node.contains(event->pos().toPoint()))
        {
            mIsEditing = true;
            mEditPolygon = mPolygon;
            mCurrentPointIndex = i;
            if (mode() == ShapeMode)
                setCursor(Qt::SizeFDiagCursor);
            if (mode() == NodeMode)
                setCursor(Qt::CrossCursor);
        }
        ++i;

    }

}

void ShapeItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    setMode(mCurrentMode == ShapeMode ? NodeMode : ShapeMode);
    update();
    QAbstractGraphicsShapeItem::mouseDoubleClickEvent(event);
}

void ShapeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    if (mIsEditing)
    {

        if (mode() == ShapeMode)
        {
            QPoint diff = event->pos().toPoint() - mPolygon.boundingRect().bottomRight();

            qreal sx = qreal(diff.x())/qreal(mPolygon.boundingRect().width()) ;
            qreal sy = qreal(diff.y())/qreal(mPolygon.boundingRect().height()) ;

            QTransform transform;
            transform.scale(sx+1,sy+1);

            mEditPolygon = transform.map(mPolygon);
        }

        if (mode() == NodeMode)
        {

            mEditPolygon[mCurrentPointIndex] = event->pos().toPoint();


        }

        update();

    }


    else
        QGraphicsItem::mouseMoveEvent(event);




}

void ShapeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    if (mIsEditing)
    {
        mIsEditing= false;
        mPolygon = mEditPolygon;
        setCursor(Qt::ArrowCursor);

    }
    else
        QGraphicsItem::mouseReleaseEvent(event);

}
