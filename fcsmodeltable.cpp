#include "fcsmodeltable.h"
#include <QVBoxLayout>
#include <QAction>
FcsModelTable::FcsModelTable(QWidget *parent) :
    QMainWindow(parent)
{

    mView = new QTableView;
    mCombo = new QComboBox;
    mModel = new FcsModel;

    mView->setModel(mModel);
    addAction(new QAction("export",this));



    QToolBar * toolbar = addToolBar("tool");
    toolbar->addWidget(mCombo);
    toolbar->addActions(actions());

    setContextMenuPolicy(Qt::ActionsContextMenu);



    setCentralWidget(mView);


    connect(mCombo,SIGNAL(currentIndexChanged(int)),this,SLOT(currentGateChanged(int)));


}

void FcsModelTable::setGateList(GateList *gateList)
{

    mModel->setGateList(gateList);
    mCombo->clear();
    foreach (QString key, gateList->keys())
    {
        mCombo->addItem(key);

    }

}

void FcsModelTable::currentGateChanged(int index)
{


    qDebug()<<mModel->gateList()->value(mCombo->currentText()).rowCount();
    mModel->setCurrentGate(mCombo->currentText());


}
