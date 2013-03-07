#ifndef GATEITEM_H
#define GATEITEM_H

#include <QGraphicsPolygonItem>

class GateItem : public QAbstractGraphicsShapeItem
{
public:
    GateItem( QGraphicsItem * parent = 0 );
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect () const ;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    void setPolygon(const QPolygonF& polygon){mPolygon = polygon;}
    void addPoint(QPointF p){ mPoints.append(p);update();}

    const QPolygonF& polygon() const {return mPolygon;}
     QPolygonF mapPolygonToScene() const;

private:
    bool mResize;
    int mPointIndex;
    QPolygonF mPolygon;
    QPolygonF mPoints;


};

#endif // GATEITEM_H
