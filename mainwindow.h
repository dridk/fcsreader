#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include "fcsfile.h"
#include "fcsinfowidget.h"
#include "fcsmodel.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public slots:
    void showFcsInfo();
    void showFcsTable();
    void showCompensationTable();
    void open();
    void createHistogramPlot();
    void createDotPlot();


private:
    Ui::MainWindow *ui;
    QMdiArea * mArea;
    FcsFile mFile;
    FcsInfoWidget * mInfoWidget;
    QTableView * mModelView;
    FcsModel * mModel;



};

#endif // MAINWINDOW_H
