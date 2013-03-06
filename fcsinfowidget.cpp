#include "fcsinfowidget.h"
#include <QVBoxLayout>
#include <QHeaderView>
FcsInfoWidget::FcsInfoWidget(FcsFile *file, QWidget *parent):
    QWidget(parent), mFile(file)
{
    mTableView = new QTableView;
    mModel = new QStandardItemModel(mFile->textSegment().count(), 2);
    mTableView->setModel(mModel);
    mTableView->verticalHeader()->hide();
    mTableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mTableView);
    setLayout(mainLayout);
    load();


}

void FcsInfoWidget::load()
{

    //    mTableView->setColumnCount(2);
    //    mTableView->setRowCount(mFile->textSegment().count());
    int row= 0;

    foreach (QString key , mFile->textSegment().keys())
    {
        QStandardItem * keyItem = new QStandardItem(key);
        QStandardItem * valItem = new QStandardItem(mFile->textSegment().value(key).toString());

        mModel->setItem(row,0,keyItem);
        mModel->setItem(row,1,valItem);
        ++row;
    }
    mTableView->resizeColumnsToContents();
}
