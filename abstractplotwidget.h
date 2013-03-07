#ifndef ABSTRACTPLOTWIDGET_H
#define ABSTRACTPLOTWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsPolygonItem>
#include "fcsdata.h"
#include "qcustomplot.h"
#include <QGraphicsView>

class AbstractPlotWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit AbstractPlotWidget(QWidget *parent = 0);
    void setFcsData(const FcsData& fcsData);
    const FcsData& fcsData() const;

    virtual void replot() = 0;

    virtual void contextMenuEvent(QContextMenuEvent *);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

    QCustomPlot * plot() {return mPlot;}

    void addPoint(QPointF p){ mPoints.append(p);update();}

    
private:
    FcsData mFcsData;
    QCustomPlot * mPlot;
    QGraphicsProxyWidget * mPlotItem;

    QList<QPointF> mPoints;
};

#endif // ABSTRACTPLOTWIDGET_H
