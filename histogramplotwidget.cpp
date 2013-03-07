#include "histogramplotwidget.h"

HistogramPlotWidget::HistogramPlotWidget(QWidget *parent) :
    AbstractPlotWidget(parent)
{



//    myBars = new QCPBars(xAxis,yAxis);
//    addPlottable(myBars);
//    // now we can modify properties of myBars:
//    myBars->setName("Pretty bars");


//    xAxis->setRange(0,1024);
//    yAxis->setRange(0,1500);
//   // xAxis->setScaleType(QCPAxis::stLogarithmic);
//    setRangeZoom(Qt::Horizontal | Qt::Vertical);


}

void HistogramPlotWidget::plot()
{


//    QVector<double> keyData(1024);
//    QVector<double> valueData(1024);
//    valueData.fill(0);

//    for (int j=0; j<1024; ++j)
//        keyData[j] = j;

//    QHash<int,int> hash;

//    qDebug()<<keyData.size();


//    for (int i=0; i<fcsData().rowCount(); ++i)
//    {

//        double val = fcsData().value(i,2);
//        valueData[val]++;

//    }


//    qDebug()<<valueData[513];
//   myBars->setData(keyData, valueData);




//   // rescaleAxes();
//    replot();

}

