#ifndef DOTPLOTWIDGET_H
#define DOTPLOTWIDGET_H
#include <QGraphicsPixmapItem>
#include "abstractplotwidget.h"
#include "fcsdata.h"
#include <QGraphicsWidget>
#include "qcustomplot.h"
#include "gateitem.h"
class DotPlotWidget : public AbstractPlotWidget
{
    Q_OBJECT
public:
    DotPlotWidget(QWidget * parent = 0);

    virtual void replot();

    void setXSection(int section);
    void setYSection(int section);

public slots:
    void addGate();
    void compute();

public slots:

private:
    int mXSection;
    int mYSection;
    GateItem * item ;





};

#endif // DOTPLOTWIDGET_H
