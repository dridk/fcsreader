#include "compensationwidget.h"
#include <QGridLayout>
#include <QTableWidget>
#include <QDebug>
#include <QHeaderView>
CompensationWidget::CompensationWidget(QWidget *parent) :
    QTableWidget(parent)
{
horizontalHeader()->setResizeMode(QHeaderView::Stretch);
verticalHeader()->setResizeMode(QHeaderView::Stretch);


}

void CompensationWidget::setup(const FcsData &data)
{

    clear();
    setRowCount(data.columnCount());
    setColumnCount(data.columnCount());


    qDebug()<<"hello";
    QStringList label;
    for  (int row=0; row< data.columnCount(); ++row)
    {
    label.append(data.headerName(row));



        for (int col = 0; col < data.columnCount(); ++col)
        {


            QTableWidgetItem * item = new QTableWidgetItem;
            if ( col == row ){
                item->setBackgroundColor(Qt::gray);
            }
            item->setText("0.0");
            setItem(row,col,item);


        }

    }

    setHorizontalHeaderLabels(label);
    setVerticalHeaderLabels(label);

    adjustSize();

}
