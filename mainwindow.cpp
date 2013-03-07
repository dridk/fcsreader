#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableView>
#include "dotplotwidget.h"
#include "histogramplotwidget.h"
#include "compensationwidget.h"
#include <QGraphicsView>
#include <QMdiSubWindow>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mArea = new QMdiArea(this);
    setCentralWidget(mArea);

    mInfoWidget = new FcsInfoWidget(&mFile);
    mModel = new FcsModel();


    mModelView = new QTableView;
    mModelView->setModel(mModel);



    connect(ui->actionFcsInfo,SIGNAL(triggered()),this,SLOT(showFcsInfo()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(open()));
    connect(ui->actionShowModel,SIGNAL(triggered()),this,SLOT(showFcsTable()));
    connect(ui->actionHistogramPlot,SIGNAL(triggered()),this,SLOT(createHistogramPlot()));
    connect(ui->actionDotPlot,SIGNAL(triggered()),this,SLOT(createDotPlot()));
    connect(ui->actionShowCompensationTable,SIGNAL(triggered()),this,SLOT(showCompensationTable()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showFcsInfo()
{
    mInfoWidget->load();
    mInfoWidget->show();
}

void MainWindow::showFcsTable()
{

    mModelView->update();
    mModelView->show();





}

void MainWindow::showCompensationTable()
{

//    CompensationWidget * widget = new CompensationWidget;
//    widget->setup(mFile.data());
//    widget->show();

}

void MainWindow::open()
{

   QString name = QFileDialog::getOpenFileName(this);
//   name = "example/exemple3.lmd";
   mFile.setFileName(name);
   // mFile.setFileName("example/exemple3.lmd");
    if (!mFile.open(QIODevice::ReadOnly))
        qDebug()<<"cannot open file";
    else {
        mFile.load();
        mModel->setSource(mFile.data());
    }
    statusBar()->showMessage(mFile.fileName());







}

void MainWindow::createHistogramPlot()
{

//HistogramPlotWidget * plot = new HistogramPlotWidget;
//plot->setFcsData(mFile.data());

//plot->plot();

//QMdiSubWindow * sub = new QMdiSubWindow;
//sub->setAttribute(Qt::WA_DeleteOnClose);
//sub->setMinimumSize(200,200);
//sub->resize(300,300);
//sub->setWidget(plot);
//sub->systemMenu()->addAction("test");
//mArea->addSubWindow(sub)->show();

}

void MainWindow::createDotPlot()
{

    DotPlotWidget * plot = new DotPlotWidget;
    plot->setFcsData(mFile.data());
    plot->setXSection(1);
    plot->setYSection(0);
    plot->replot();

    QMdiSubWindow * sub = new QMdiSubWindow;
    sub->setAttribute(Qt::WA_DeleteOnClose);
    sub->setMinimumSize(200,200);
    sub->resize(300,300);
    sub->setWidget(plot);
    sub->systemMenu()->addAction("test");
    mArea->addSubWindow(sub)->show();


}
