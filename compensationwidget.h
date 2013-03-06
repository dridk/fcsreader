#ifndef COMPENSATIONWIDGET_H
#define COMPENSATIONWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include "fcsdata.h"
class CompensationWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit CompensationWidget(QWidget *parent = 0);
    void setup(const FcsData& data);
    
signals:
    
public slots:
    
};

#endif // COMPENSATIONWIDGET_H
