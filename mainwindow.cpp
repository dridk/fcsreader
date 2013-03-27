/***************************************************************************
**                                                                        **
**  FcsViewer, a simple cytometry data viewer made with Qt4 and           **
**  customplot made by Emanuel Eichhammer                                 **
**  Copyright (C) 2013 Sacha Schutz                                       **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author : Sacha Schutz                                        **
**           Website: http://www.labsquare.org                            **
**           Email  : sacha@labsquare.org                                 **
**           Date   : 12.03.12                                            **
****************************************************************************/


#include <QTableView>
#include <QGraphicsView>
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QDockWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dotplotwidget.h"
#include "propertywidgetcontainer.h"
#include "scatterstylecombobox.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    mArea = new QMdiArea(this);
    mRootGate = new Gate();
    mStatWidget = new StatisticsWidget;
    mGateTreeWidget = new GateTreeWidget;
    mOptionDockWidget = new QDockWidget;

    mOptionDockWidget->setVisible(false);
    mOptionDockWidget->setMinimumWidth(300);
    mRootGate->setName("All");



    QDockWidget * statDockWidget = new QDockWidget;
    QDockWidget * gateDockWidget = new QDockWidget;
    //    statDockWidget->setWindowTitle(mStatWidget->windowTitle());
    //    gateDockWidget->setWindowTitle(mGateTreeWidget->windowTitle());



    //    statDockWidget->setWidget(mStatWidget);
    gateDockWidget->setWidget(mGateTreeWidget);

    addDockWidget(Qt::LeftDockWidgetArea,statDockWidget);
    addDockWidget(Qt::LeftDockWidgetArea,gateDockWidget);
    addDockWidget(Qt::RightDockWidgetArea,mOptionDockWidget);

    setCentralWidget(mArea);

    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(open()));
    connect(ui->actionDotplot,SIGNAL(triggered()),this,SLOT(addDotPlot()));
    connect(mArea,SIGNAL(subWindowActivated(QMdiSubWindow*)),this,SLOT(subWindowActivated(QMdiSubWindow*)));



    showMaximized();

    //    connect(ui->actionFcsInfo,SIGNAL(triggered()),this,SLOT(showFcsInfo()));
    //    connect(ui->actionShowModel,SIGNAL(triggered()),this,SLOT(showFcsTable()));
    //    connect(ui->actionHistogramPlot,SIGNAL(triggered()),this,SLOT(createHistogramPlot()));
    //    connect(ui->actionDotPlot,SIGNAL(triggered()),this,SLOT(createDotPlot()));
    //    connect(ui->actionShowCompensationTable,SIGNAL(triggered()),this,SLOT(showCompensationTable()));

}


MainWindow::~MainWindow()
{
    delete ui;
    mFile.close();
    delete mRootGate;
    delete mStatWidget;
    delete mGateTreeWidget;
    delete mOptionDockWidget;
    delete mArea;

}

//void MainWindow::showFcsInfo()
//{
//    mInfoWidget->load();
//    mInfoWidget->show();
//}

//void MainWindow::showFcsTable()
//{


//    mTableView->setGateList(&mGates);
//    mTableView->show();




//}

//void MainWindow::showCompensationTable()
//{

//    CompensationWidget * widget = new CompensationWidget;
//    widget->setup(mFile.data());
//    widget->show();

//}

void MainWindow::open()
{

//    QString filename = QFileDialog::getOpenFileName();
//    mFile.setFileName(filename);

     mFile.setFileName("/home/schutz/example.LMD");


    if(mFile.open()){
        statusBar()->showMessage(mFile.fileName());
        mRootGate->setData(mFile.data());
        mGateTreeWidget->gateModel()->setGate(mRootGate);




    }
}

void MainWindow::addDotPlot()
{

    DotPlotWidget * widget = new DotPlotWidget(mRootGate);
    QMdiSubWindow * sub = new QMdiSubWindow;
   // connect(widget,SIGNAL(destroyed()),sub,SLOT(close()));
    sub->setWidget(widget);
    mOptionDockWidget->setVisible(true);
    mArea->addSubWindow(sub);
    widget->replot();
    sub->show();

    connect(sub,SIGNAL(destroyed()),sub,SLOT(close()));

}

void MainWindow::showStatistics()
{
}

void MainWindow::subWindowActivated(QMdiSubWindow *sub)
{

    if (sub)
    {
        if (sub->widget()->metaObject()->className() == QString("DotPlotWidget"))
        {
            AbstractPlotWidget * plot = qobject_cast<AbstractPlotWidget*>(sub->widget());
            mStatWidget->setStatsData(plot->statsData());
            ui->plotToolBar->addActions(plot->actions());


            mOptionDockWidget->setWidget(plot->propertyListWidget());

        }

    }







}

//void MainWindow::createHistogramPlot()
//{

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

//}

//void MainWindow::createDotPlot()
//{

//    DotPlotWidget * plot = new DotPlotWidget;
//    plot->setGateList(&mGates);
//    plot->setXSection(1);
//    plot->setYSection(0);
//    plot->setGateName("all");
//    plot->replot();

//    QMdiSubWindow * sub = new QMdiSubWindow;
//    sub->setAttribute(Qt::WA_DeleteOnClose);
//    sub->setMinimumSize(200,200);
//    sub->resize(300,300);
//    sub->setWidget(plot);
//    sub->systemMenu()->addAction("test");
//    mArea->addSubWindow(sub)->show();


//}

