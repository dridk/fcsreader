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
    virtual void init();

    void setXSection(int section);
    void setYSection(int section);
    void setGateName(const QString& gateName);

    FcsData dataGated(GateItem * gateItem);

public slots:
    void addGate();
    void compute();
    void computeAllGate();
    void actionTriggered();

protected:


private:
    int mXSection;
    int mYSection;
    QString mGateName;
    QList<GateItem*> mGates;
    QCPDataMap mDataMap;

    QMenu * mGateMenu;
    QMenu * mXMenu;
    QMenu * mYMenu;





};

#endif // DOTPLOTWIDGET_H
