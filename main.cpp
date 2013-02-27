#include <QtGui/QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "fcsfile.h"
#include <QListWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QListWidget * widget = new QListWidget;
    widget->show();

    FcsFile file("example/example.lmd");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug()<<"cannot open file";

QVariantMap map =file.textSegment();

    foreach (QString key, map.keys())
    {
        QListWidgetItem * item =new QListWidgetItem;
        item->setText(key+" : "+map.value(key).toString());
        widget->addItem(item);
    }


file.close();;
    MainWindow w;
    w.show();
    
    return a.exec();
}
