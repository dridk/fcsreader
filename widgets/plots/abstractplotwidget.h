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
    explicit AbstractPlotWidget(Gate * gate, QWidget *parent = 0);
    QCustomPlot * plot() {return mPlot;}

    void setTitle(const QString& title);
    const QString& title() const;

    Gate * gate();

    PropertyListWidget* propertyListWidget() {return mPropertyWidget;}
    GatePropertyWidget* gatePropertyWidget() {return mGatePropertyWidget;}
    DisplayPropertyWidget * displayPropertyWidget() {return mCommonPropertyWidget;}
    virtual StatsData statsData() ;

public slots:
    virtual void replot() = 0;
    void setGate(Gate * gate);
signals:
    void gateChanged();



protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

    void setupProperty();
    
private:
    QCustomPlot * mPlot;
    QGraphicsProxyWidget * mPlotItem;
    Gate * mGate;
    PropertyListWidget * mPropertyWidget;

    //Common property widget
    GatePropertyWidget * mGatePropertyWidget;
    DisplayPropertyWidget * mCommonPropertyWidget;
};

#endif // ABSTRACTPLOTWIDGET_H
