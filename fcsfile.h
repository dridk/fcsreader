#ifndef FCSFILE_H
#define FCSFILE_H

#include <QFile>
#include <QHash>
#include <QString>
#include <QVariantMap>
#include <QtCore>
class FcsFile : public QFile
{
public:
    FcsFile(QObject * parent = 0);
    FcsFile(const QString& name);
    QString version();
    QVariantMap textSegment();
    int parameterCount();
    int eventCount();
    QDateTime aquisitionDate();
    QList<QVariantList> dataSegment();


protected:
    int textBeginOffset();
    int textEndOffset();
    int dataBeginOffset();
    int dataEndOffset();




};

#endif // FCSFILE_H
