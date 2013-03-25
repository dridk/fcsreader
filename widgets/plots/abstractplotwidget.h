#ifndef ABSTRACTPLOTWIDGET_H
#define ABSTRACTPLOTWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsPolygonItem>
#include <QMap>
#include <QMenu>
#include <QGraphicsView>
#include <QContextMenuEvent>
#include <QMainWindow>
#include "gate.h"
#include "fcsdata.h"
#include "qcustomplot.h"
#include "statisticswidget.h"
#include "propertylistwidget.h"
#include "gatepropertywidget.h"
#include "displaypropertywidget.h"

class AbstractPlotWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit AbstractPlotWidget(Gate * rootGate, QWidget *parent = 0);
    QCustomPlot * plot() {return mPlot;}

    void setTitle(const QString& title);
    const QString& title() const;

    void setGate(Gate * rootGate);
    Gate * rootGate();

    PropertyListWidget * propertyListWidget() {return mPropertyWidget;}

    virtual StatsData statsData() ;

public slots:
    virtual void replot() = 0;





protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

    void setupProperty();
    
private:
    QCustomPlot * mPlot;
    QGraphicsProxyWidget * mPlotItem;
    Gate * mRootGate;
    PropertyListWidget * mPropertyWidget;

    //Common property widget
    GatePropertyWidget * mGatePropertyWidget;
    DisplayPropertyWidget * mCommonPropertyWidget;
};

#endif // ABSTRACTPLOTWIDGET_H
