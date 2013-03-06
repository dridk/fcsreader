#ifndef HISTOGRAMPLOTWIDGET_H
#define HISTOGRAMPLOTWIDGET_H
#include "abstractplotwidget.h"
class HistogramPlotWidget : public AbstractPlotWidget
{
    Q_OBJECT
public:
    explicit HistogramPlotWidget(QWidget *parent = 0);
    
    void plot();
signals:
    
public slots:
private:
    QCPBars *myBars;
};

#endif // HISTOGRAMPLOTWIDGET_H
