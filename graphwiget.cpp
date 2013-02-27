#include "graphwiget.h"
#include <QPainter>
GraphWiget::GraphWiget(QWidget *parent) :
    QWidget(parent)
{
}

void GraphWiget::paintEvent(QPaintEvent *event)
{


    QPainter paint(this);


    paint.setBrush(QBrush(Qt::white));
    QRect zone = rect().adjusted(10,10,-10,-10);
    paint.drawRect(zone);
    paint.setPen(QPen(Qt::red));


QMatrix m;
m.translate(1,zone.height() + 10);
m.scale(1,-1);

paint.setMatrix(m);

    for (int i=0; i<mXData.count(); ++i)
    {
        int x = mXData.at(i).toInt() * zone.width() / 1024;
        int y = mYData.at(i).toInt() * zone.height() / 1024;

        paint.drawPoint(x,y);

    }






}

void GraphWiget::setData(const QVariantList &xdata, const QVariantList &ydata)
{
    mXData = xdata;
    mYData = ydata;
}
