#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableView>
#include "dotplotwidget.h"
#include "histogramplotwidget.h"
#include "compensationwidget.h"
#include <QGraphicsView>
#include <QMdiSubWindow>
#include <QFileDialog>
#include "fcsmodeltable.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mArea = new QMdiArea(this);
    setCentralWidget(mArea);

    mInfoWidget = new FcsInfoWidget(&mFile);



    mTableView = new FcsModelTable;



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


    mTableView->setGateList(&mGates);
    mTableView->show();




}

void MainWindow::showCompensationTable()
{

//    CompensationWidget * widget = new CompensationWidget;
//    widget->setup(mFile.data());
//    widget->show();

}

void MainWindow::open()
{

//   QString name = QFileDialog::getOpenFileName(this);
   QString name = "/home/schutz/example.LMD";
   mFile.setFileName(name);
   // mFile.setFileName("/home/schutz/cyto.lmd");
    if (!mFile.open(QIODevice::ReadOnly))
        qDebug()<<"cannot open file";
    else {
        mFile.load();
        mGates.insert("all",mFile.data());

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
    plot->setGateList(&mGates);
    plot->setXSection(1);
    plot->setYSection(0);
    plot->setGateName("all");
    plot->replot();

    QMdiSubWindow * sub = new QMdiSubWindow;
    sub->setAttribute(Qt::WA_DeleteOnClose);
    sub->setMinimumSize(200,200);
    sub->resize(300,300);
    sub->setWidget(plot);
    sub->systemMenu()->addAction("test");
    mArea->addSubWindow(sub)->show();


}
