#ifndef DOTPLOTWIDGET_H
#define DOTPLOTWIDGET_H
#include <QGraphicsPixmapItem>
#include "abstractplotwidget.h"
#include "fcsdata.h"
#include <QGraphicsWidget>
#include "qcustomplot.h"
class DotPlotWidget : public AbstractPlotWidget
{
Q_OBJECT
public:
    DotPlotWidget(QWidget * parent = 0);
    virtual void plot();

    void setXSection(int section);
    void setYSection(int section);

public slots:
    void legendClicked(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*);

private:
    int mXSection;
    int mYSection;




};

#endif // DOTPLOTWIDGET_H
