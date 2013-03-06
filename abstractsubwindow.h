#ifndef ABSTRACTSUBWINDOW_H
#define ABSTRACTSUBWINDOW_H

#include <QMdiSubWindow>

class AbstractSubWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit AbstractSubWindow(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // ABSTRACTSUBWINDOW_H
