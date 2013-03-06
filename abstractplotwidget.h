#ifndef ABSTRACTPLOTWIDGET_H
#define ABSTRACTPLOTWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsPolygonItem>
#include "fcsdata.h"
#include "qcustomplot.h"


class AbstractPlotWidget : public QCustomPlot
{
    Q_OBJECT
public:
    explicit AbstractPlotWidget(QWidget *parent = 0);
    void setFcsData(const FcsData& fcsData);
    const FcsData& fcsData() const;

    virtual void plot() = 0;

    virtual void contextMenuEvent(QContextMenuEvent *);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    
private:
    FcsData mFcsData;
};

#endif // ABSTRACTPLOTWIDGET_H
