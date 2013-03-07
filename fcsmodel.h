#ifndef FCSMODEL_H
#define FCSMODEL_H
#include <QFile>
#include <QtCore>
#include <QAbstractTableModel>
#include <QBuffer>
#include "fcsdata.h"

class FcsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit FcsModel( QObject *parent = 0);
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void setSource(const FcsData& data);
    void update();


private:
    FcsData mFcsData;


    
};

#endif // FCSMODEL_H