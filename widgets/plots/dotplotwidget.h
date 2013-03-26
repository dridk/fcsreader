#ifndef DOTPLOTWIDGET_H
#define DOTPLOTWIDGET_H
#include <QGraphicsPixmapItem>
#include <QGraphicsWidget>
#include "abstractplotwidget.h"
#include "dotplotpropertywidget.h"
#include "shapeitem.h"
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
    void setGateEditing(bool editing);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
protected slots:
    void computeGate();



private:
    DotPlotPropertyWidget * mPropertyWidget;
    int mXField;
    int mYField;
    QGraphicsPolygonItem * mGateEditItem;
    QList<ShapeItem*> mShapeItems;



};

#endif // DOTPLOTWIDGET_H
