#include "dotplotwidget.h"
#include <QDebug>
#include <QMatrix>
#include <QGraphicsProxyWidget>
#include <QAction>
#include "qcustomplot.h"
#include <QContextMenuEvent>
#include <QMenu>


DotPlotWidget::DotPlotWidget(QWidget *parent) :
    AbstractPlotWidget(parent)

{

    mGateName = "all";

    mGateMenu = new QMenu("gate",this);
    mXMenu = new QMenu("X",this);
    mYMenu = new QMenu("Y",this);

    menu()->addMenu(mGateMenu);
    menu()->addMenu(mXMenu);
    menu()->addMenu(mYMenu);

    connect(menu()->addAction("add gate"),SIGNAL(triggered()),this,SLOT(addGate()));
    connect(menu()->addAction("replot"),SIGNAL(triggered()),this,SLOT(replot()));


    //    connect(actions()[0],SIGNAL(triggered()),this,SLOT(addGate()));
    //    connect(actions()[1],SIGNAL(triggered()),this,SLOT(compute()));
    //    connect(actions()[2],SIGNAL(triggered()),this,SLOT(replot()));

    plot()->graph()->setPen(QPen(Qt::blue));
    plot()->xAxis->setRange(0,1024);
    plot()->yAxis->setRange(0,1024);



    //    graph(0)->setName("test");
    plot()->graph()->setLineStyle(QCPGraph::lsNone);
    plot()->graph()->setScatterStyle(QCP::ssDot);
    //    graph(0)->setSelectable(true);

    //    addAction(new QAction("salut",this));
    //    setContextMenuPolicy(Qt::ActionsContextMenu);

    plot()->setRangeZoom(Qt::Horizontal | Qt::Vertical);




}

void DotPlotWidget::replot()
{

    mDataMap.clear();

    for (int i=0; i<gateList()->value(mGateName).rowCount(); ++i)
    {
        double x = gateList()->value(mGateName).valueAtCoord(i,mXSection);
        double y = gateList()->value(mGateName).valueAtCoord(i,mYSection);
        QCPData newsData;
        newsData.key = x;
        newsData.value = y;
        newsData.index = i;
        mDataMap.insertMulti(x,newsData);


    }

    plot()->graph()->setData(&mDataMap,true);
    plot()->rescaleAxes();
    plot()->replot();

    qDebug()<<"plot";

}

void DotPlotWidget::init()
{



    foreach (QString key,  gateList()->keys())
    {
        QAction * action = mGateMenu->addAction(key);
        action->setObjectName("gate");
        connect(action,SIGNAL(triggered()),this,SLOT(actionTriggered()));
    }


    for (int i=0; i<gateList()->value("all").columnCount(); ++i)
    {
        QAction * ax = mXMenu->addAction(gateList()->value("all").headerName(i));
        QAction * ay = mYMenu->addAction(gateList()->value("all").headerName(i));

        ax->setObjectName("x");
        ay->setObjectName("y");
        ax->setData(i);
        ay->setData(i);

        connect(ax,SIGNAL(triggered()),this,SLOT(actionTriggered()));
        connect(ay,SIGNAL(triggered()),this,SLOT(actionTriggered()));
    }






}


void DotPlotWidget::setXSection(int section)
{
    mXSection = section;
    plot()->xAxis->setLabel(gateList()->value(mGateName).headerName(mXSection));
}

void DotPlotWidget::setYSection(int section)
{
    mYSection = section;
    plot()->yAxis->setLabel(gateList()->value(mGateName).headerName(mYSection));

}

void DotPlotWidget::setGateName(const QString& gateName)
{
    mGateName = gateName;
    plot()->setTitle(mGateName);

}

FcsData DotPlotWidget::dataGated(GateItem *gateItem)
{
    QPolygonF poly = gateItem->mapPolygonToScene();
    QVector<int> rows;
    foreach ( QCPData data, plot()->graph()->data()->values())
    {
        double x  = plot()->xAxis->coordToPixel(data.key);
        double y  = plot()->yAxis->coordToPixel(data.value);

        if (poly.containsPoint( QPointF(x,y),Qt::WindingFill))
            rows.append(data.index);

    }

    qDebug()<<rows.count()<<" evenements";

    FcsData test = gateList()->value(mGateName);
    test.clear();
    foreach (int row,  rows)
        test.appendRow(row);

    return test;
}

void DotPlotWidget::addGate()
{


    GateItem * item  = new GateItem;
    item->setPolygon(QPolygonF(QRectF(0,0,40,40)));
    item->setBrush(QBrush(QColor(255,0,0,30)));
    item->setPen(QPen(Qt::blue));
    scene()->addItem(item);
    mGates.append(item);

    item->setObjectName(QString::number((int)(item),16));
    connect(item,SIGNAL(positionChanged()),this,SLOT(compute()));





}

void DotPlotWidget::compute()
{
    qDebug()<<"compute ";

    GateItem * item = qobject_cast<GateItem*>(sender());
    FcsData data = dataGated(item);
    QString id = QString::number((int)item);

    gateList()->insert(id, data);


}

void DotPlotWidget::computeAllGate()
{




}

void DotPlotWidget::actionTriggered()
{

    QAction * action = qobject_cast<QAction*>(sender());
    if (sender()->objectName() == "gate")
        setGateName(action->text());

    if (sender()->objectName() == "x")
        setXSection( action->data().toInt());

    if (sender()->objectName() == "y")
        setYSection(action->data().toInt());



    replot();


}









