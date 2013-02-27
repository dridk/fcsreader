#include "fcsfile.h"
#include <QByteArray>
#include <QDebug>
FcsFile::FcsFile(QObject *parent)
    :QFile(parent)
{
}

FcsFile::FcsFile(const QString &name)
    :QFile(name)
{
}

QVariantMap FcsFile::textSegment()
{

    int begin = textBeginOffset();
    int end = textEndOffset();

    seek(begin);

    QString textData = QString::fromAscii(read(end-begin));


    QVariantMap map;
    foreach (QString pair, textData.split(QRegExp("\\$|@")))
    {
        pair = pair.remove(pair.length()-1,1); //remove last slash

        QStringList pairList= pair.split(QRegExp("\\\\{1}"));
        QString key = pairList.first();
        QVariant value = pairList.length() > 1 ? pairList.at(1) : 0;
        map.insert(key,value);
    }



return map;

}

QString FcsFile::version()
{
    seek(0);
    return QString(read(6));
}

int FcsFile::textBeginOffset()
{
    seek(10);
    return  read(8).toInt();
}

int FcsFile::textEndOffset()
{
    seek(18);
    return read(8).toInt();
}

int FcsFile::dataBeginOffset()
{
    seek(26);
    return read(8).toInt();
}

int FcsFile::dataEndOffset()
{
    seek(34);
    return read(8).toInt();
}

