#ifndef FCSINFOWIDGET_H
#define FCSINFOWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include "fcsfile.h"
class FcsInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FcsInfoWidget(FcsFile * file , QWidget *parent = 0);

public slots:
    void load();

private:
    FcsFile * mFile;
    QTableView * mTableView;
    QStandardItemModel * mModel;
};

#endif // FCSINFOWIDGET_H
