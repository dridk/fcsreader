#ifndef FCSFILE_H
#define FCSFILE_H

#include <QFile>
#include <QHash>
#include <QString>
#include <QVariantMap>
#include <QtCore>
#include "fcsdata.h"
class FcsFile : public QFile
{
public:
    FcsFile(QObject * parent = 0);
    FcsFile(const QString& fileName, QObject * parent = 0);
    ~FcsFile();
    QString version();
    const QVariantMap& textSegment() const ;
    QVector<double> * dataSegment();
    FcsData data() ;
    void load();

    void test();

    int parameterCount() const;
    int eventCount() const ;
    QDateTime aquisitionDate() const ;


protected:
    int textBeginOffset() ;
    int textEndOffset();
    int dataBeginOffset();
    int dataEndOffset();

    void loadTextSegment();
    void loadDataSegment();

private:
    QVariantMap mTextSegment;
    QVector<double> mDataSegment;





};

#endif // FCSFILE_H
