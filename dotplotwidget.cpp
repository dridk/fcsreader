#include "dotplotwidget.h"
#include <QDebug>
#include <QMatrix>
#include <QGraphicsProxyWidget>
#include <QAction>
#include "qcustomplot.h"
DotPlotWidget::DotPlotWidget(QWidget *parent) :
    AbstractPlotWidget(parent)

{


    addAction(new QAction("add gate",this));
    addAction(new QAction("compute",this));
    setContextMenuPolicy(Qt::ActionsContextMenu);

    connect(actions()[0],SIGNAL(triggered()),this,SLOT(addGate()));
    connect(actions()[1],SIGNAL(triggered()),this,SLOT(compute()));

    plot()->xAxis->setRange(0,1024);
    plot()->yAxis->setRange(0,1024);


    //    graph(0)->setName("test");
    plot()->graph()->setLineStyle(QCPGraph::lsNone);
    plot()->graph()->setScatterStyle(QCP::ssDot);
    //    graph(0)->setSelectable(true);

    //    addAction(new QAction("salut",this));
    //    setContextMenuPolicy(Qt::ActionsContextMenu);

    //    setRangeZoom(Qt::Horizontal | Qt::Vertical);
    ;




}

void DotPlotWidget::replot()
{

    //    plot()->xAxis->setLabel(fcsData().headerName(mXSection));
    //    plot()->yAxis->setLabel(fcsData().headerName(mYSection));

    //    qDebug()<<fcsData().rowCount();


    QVector<double> x;
    QVector<double> y;

    for (int i=0; i<fcsData().rowCount(); ++i)
    {


        x.append(fcsData().value(i,mXSection));
        y.append(fcsData().value(i,mYSection));

        //    plot()->graph()->setData(x,y);
        //    plot()->rescaleAxes();



    }

    plot()->graph()->setData(x,y);
    plot()->rescaleAxes();
    plot()->replot();


}


void DotPlotWidget::setXSection(int section)
{
    mXSection = section;
}

void DotPlotWidget::setYSection(int section)
{
    mYSection = section;
}

void DotPlotWidget::addGate()
{

    item =new GateItem;
    item->setPolygon(QPolygonF(QRectF(0,0,40,40)));
    item->setBrush(QBrush(QColor(255,255,0,50)));

    scene()->addItem(item);


}

void DotPlotWidget::compute()
{


    QPolygonF poly = item->mapPolygonToScene();

    QVector<double> test;


    qDebug()<<plot()->graph()->data()->size();
    qDebug()<<fcsData().rowCount();

    foreach ( QCPData data, plot()->graph()->data()->values())
    {
        double x  = plot()->xAxis->coordToPixel(data.key);
        double y = plot()->yAxis->coordToPixel(data.value);

        QPointF pos(x,y);


        if (poly.containsPoint(pos,Qt::WindingFill))
        {
            test.append(1);
        }
    }

    scene()->addPolygon(poly);
    qDebug()<<"il y a "<<test.size()<<" evenement dans cette gates";

}







