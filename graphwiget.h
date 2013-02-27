#ifndef GRAPHWIGET_H
#define GRAPHWIGET_H

#include <QWidget>
#include <QPainter>
#include <QtCore>
class GraphWiget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphWiget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);

    void setData(const QVariantList& xdata, const QVariantList& ydata);
    
private:

QVariantList mXData;
QVariantList mYData;
QImage mImage;
    
};

#endif // GRAPHWIGET_H
