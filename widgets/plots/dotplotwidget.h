#ifndef DOTPLOTWIDGET_H
#define DOTPLOTWIDGET_H
#include <QGraphicsPixmapItem>
#include <QGraphicsWidget>
#include "abstractplotwidget.h"
#include "dotplotpropertywidget.h"

class DotPlotWidget : public AbstractPlotWidget
{
    Q_OBJECT
public:
    DotPlotWidget(Gate * rootGate, QWidget * parent = 0);
    virtual void replot();




public slots:
    void setXField(int col);
    void setYField(int col);
    void setXLabel(const QString& label = QString());
    void setYLabel(const QString& label= QString());


protected:


private:
    DotPlotPropertyWidget * mPropertyWidget;
    int mXField;
    int mYField;



};

#endif // DOTPLOTWIDGET_H
