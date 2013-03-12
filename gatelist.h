#ifndef GATELIST_H
#define GATELIST_H

#include <QObject>
#include <QMap>
#include <QStringList>
#include "fcsdata.h"
class GateList : public QMap<QString,FcsData>
{

public:
    explicit GateList();


    
};

#endif // GATELIST_H
