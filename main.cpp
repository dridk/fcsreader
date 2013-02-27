#include <QtGui/QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "fcsfile.h"
#include <QListWidget>
#include <QTableWidget>
#include "graphwiget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QTableWidget * widget = new QTableWidget;
    widget->show();

    GraphWiget * graph = new GraphWiget;


    FcsFile file("example/exemple3.lmd");
    if (!file.open(QIODevice::ReadOnly))
        qDebug()<<"cannot open file";


    widget->setColumnCount(file.parameterCount());
    widget->setRowCount(file.eventCount());



    int column = 0;

    QList<QVariantList> allData =  file.dataSegment();

    foreach (QVariantList item,allData)
    {
        int row = 0;
        foreach (QVariant value, item)
        {
            QTableWidgetItem * t = new QTableWidgetItem;
            t->setText(value.toString());
            widget->setItem(row,column,t);
            ++row;
        }

        QTableWidgetItem * header = new QTableWidgetItem;
        header->setText(file.textSegment().value(QString("P%1N").arg(column+1)).toString());
        widget->setHorizontalHeaderItem(column,header);
        ++column;
    }



    graph->show();
    graph->setData(allData.at(0), allData.at(1));

    file.close();

    return a.exec();
}
