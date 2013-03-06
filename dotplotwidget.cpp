#include "dotplotwidget.h"
#include <QDebug>
#include <QMatrix>
#include <QGraphicsProxyWidget>
#include <QAction>
#include "qcustomplot.h"
DotPlotWidget::DotPlotWidget(QWidget *parent) :
    AbstractPlotWidget(parent)

{
    xAxis->setRange(0,1024);
    yAxis->setRange(0,1024);


    legend->setVisible(true);

    addGraph();
    graph(0)->setName("test");
    graph(0)->setLineStyle(QCPGraph::lsNone);
    graph(0)->setScatterStyle(QCP::ssPlus);
    graph(0)->setSelectable(true);

    addAction(new QAction("salut",this));
    setContextMenuPolicy(Qt::ActionsContextMenu);

    setRangeZoom(Qt::Horizontal | Qt::Vertical);
;

}

void DotPlotWidget::plot()
{

    xAxis->setLabel(fcsData().headerName(mXSection));
    yAxis->setLabel(fcsData().headerName(mYSection));

    QVector<double> x(fcsData().rowCount());
    QVector<double> y(fcsData().rowCount());

    for (int i=0; i<fcsData().rowCount(); ++i)
    {
        x[i] = fcsData().value(i,mXSection);
        y[i] = fcsData().value(i,mYSection);
    }



    graph(0)->setData(x,y);
    rescaleAxes();



}

void DotPlotWidget::setXSection(int section)
{
    mXSection = section;
}

void DotPlotWidget::setYSection(int section)
{
    mYSection = section;
}

void DotPlotWidget::legendClicked(QCPLegend * legend, QCPAbstractLegendItem *, QMouseEvent *)
{
    qDebug()<<"legend clicked";
}



//    plot->xAxis->setRange(0,1024);
//    plot->yAxis->setRange(0,1024);

//  plot->addGraph();
//plot->graph(0)->setScatterSize(2);
//plot->graph(0)->setScatterStyle(QCP::ssPlus);
//plot->graph(0)->setLineStyle(QCPGraph::lsNone);
//plot->setInteraction(QCustomPlot::iSelectPlottables);

//connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plot->xAxis2, SLOT(setRange(QCPRange)));
//connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));


//    widget = new QGraphicsProxyWidget;

//    widget->setWidget(plot);

//   draw();



//    scene()->setSceneRect(0,0,1024,1024);
//    mRectItem->setBrush(QBrush(Qt::red));
//    scene()->addItem(mRectItem);
//    scene()->addItem(mItem);


//scene()->setBackgroundBrush(QBrush(QColor(255)));

//}



//void DotPlotWidget::draw()
//{


//    QVector<double> x(data().rowCount());
//    QVector<double> y(data().rowCount());

//        for (int i=0; i<data().rowCount(); ++i)
//        {

//            x[i] = data().value(i,1);
//            y[i] = data().value(i,0);

//        }



//        plot->graph(0)->setData(x,y);

//        plot->graph(0)->rescaleAxes();

//        plot->setRangeZoom(Qt::Horizontal | Qt::Vertical);

//        paint.setPen(QPen(Qt::red));

//        paint.drawPoint(0,0);
//        paint.drawPoint(1,1);
//         paint.drawPoint(10,10);

//    paint.end();

//    mItem->setPixmap(mPixmap);


//}





