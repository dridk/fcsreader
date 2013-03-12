#ifndef FCSMODELTABLE_H
#define FCSMODELTABLE_H

#include <QWidget>
#include <QComboBox>
#include <QToolBar>
#include <QTableView>
#include <QMainWindow>
#include <QMap>
#include "fcsdata.h"
#include "fcsmodel.h"
#include "gatelist.h"
class FcsModelTable : public QMainWindow
{
    Q_OBJECT
public:
    explicit FcsModelTable(QWidget *parent = 0);

    
public slots:
    void setGateList(GateList * gateList);

protected slots:
    void currentGateChanged(int index);

private:
    QTableView * mView;
    QToolBar * mToolBar;
    QComboBox * mCombo;
    GateList * mGateList;
    FcsModel * mModel;

    
};

#endif // FCSMODELTABLE_H
