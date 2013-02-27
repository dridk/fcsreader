#include "graphwiget.h"
#include <QPainter>
#include <QRgb>
GraphWiget::GraphWiget(QWidget *parent) :
    QWidget(parent)
{
}

void GraphWiget::paintEvent(QPaintEvent *event)
{


    QPainter paint(this);

    paint.drawImage(0,0,mImage);

    //    paint.setBrush(QBrush(Qt::white));
    //    QRect zone = rect().adjusted(10,10,-10,-10);
    //    paint.drawRect(zone);
    //    paint.setPen(QPen(Qt::red));


    //QMatrix m;
    //m.translate(1,zone.height() + 10);
    //m.scale(1,-1);

    //paint.setMatrix(m);

    //    for (int i=0; i<mXData.count(); ++i)
    //    {
    //        int x = mXData.at(i).toInt() * zone.width() / 1024;
    //        int y = mYData.at(i).toInt() * zone.height() / 1024;

    //        paint.drawPoint(x,y);

    //    }






}

void GraphWiget::setData(const QVariantList &xdata, const QVariantList &ydata)
{
    mXData = xdata;
    mYData = ydata;

    QRect zone = rect();
    mImage = QImage(zone.size(),QImage::Format_RGB16);
    mImage.fill(Qt::white);

    QPainter paint(&mImage);

    QMatrix m;
    m.translate(1,zone.height() );
    m.scale(1,-1);

    paint.setMatrix(m);

    for (int i=0; i<mXData.count(); ++i)
    {
        int x = mXData.at(i).toInt() * zone.width() / 1024;
        int y = mYData.at(i).toInt() * zone.height() / 1024;

        QColor col = Qt::black;
        QColor pixelColor = QColor::fromRgb(mImage.pixel(x,y));
        if (pixelColor.name() == QColor("white").name())
            col = Qt::blue;
        else {
            col = pixelColor.lighter();
    }

        QPen pen;
        pen.setColor(col);
        pen.setWidth(1);
paint.setPen(pen);
       paint.drawPoint(x,y);




    }





}
