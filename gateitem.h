#ifndef GATEITEM_H
#define GATEITEM_H

#include <QGraphicsPolygonItem>
#include <QGraphicsObject>
#include <QPainter>
class GateItem : public QGraphicsObject
{
    Q_OBJECT
public:
    GateItem( QGraphicsItem * parent = 0 );
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect () const ;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);

    void setPolygon(const QPolygonF& polygon){mPolygon = polygon;}
    void addPoint(QPointF p){ mPoints.append(p);update();}

    const QPolygonF& polygon() const {return mPolygon;}
     QPolygonF mapPolygonToScene() const;

     void setBrush(const QBrush& brush){mBrush = brush;}
     void setPen(const QPen& pen){mPen = pen;}
     const QBrush& brush() const {return mBrush;}
     const QPen& pen() const { return mPen; }

signals:
     void positionChanged();

private:
    bool mResize;
    int mPointIndex;
    QPolygonF mPolygon;
    QPolygonF mPoints;
    QBrush mBrush;
    QPen mPen;


};

#endif // GATEITEM_H
