#include <QtGui/QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "fcsfile.h"
#include <QListWidget>
#include <QTableWidget>

#include "graphwiget.h"
#include "fcsmodel.h"
#include "fcsinfowidget.h"
#include "qcustomplot.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);




        MainWindow mainwindow;
        mainwindow.show();







    return a.exec();
}
