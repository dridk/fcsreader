#ifndef ABSTRACTPLOTWIDGET_H
#define ABSTRACTPLOTWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsPolygonItem>
#include "fcsdata.h"
#include "qcustomplot.h"
#include <QMap>
#include <QMenu>
#include <QGraphicsView>
#include <QContextMenuEvent>
#include "gatelist.h"
class AbstractPlotWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit AbstractPlotWidget(QWidget *parent = 0);
    void setGateList(GateList * mapDatas);
    GateList *  gateList() const;
    QCustomPlot * plot() {return mPlot;}
    void addPoint(QPointF p){ mPoints.append(p);update();}
    QMenu * menu() {return mMenu;}

public slots:
    virtual void replot() = 0;
    virtual void init() = 0;

protected:
    virtual void contextMenuEvent(QContextMenuEvent *);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

    
private:
    GateList *  mGateList;
    QCustomPlot * mPlot;
    QGraphicsProxyWidget * mPlotItem;
    QList<QPointF> mPoints;
    QMenu * mMenu;
};

#endif // ABSTRACTPLOTWIDGET_H
