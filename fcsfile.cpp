#include "fcsfile.h"
#include <QByteArray>
#include <QDebug>
#include <QDataStream>

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

int FcsFile::parameterCount()
{
    return textSegment().value("PAR").toInt();
}

int FcsFile::eventCount()
{
    return textSegment().value("TOT").toInt();
}

QDateTime FcsFile::aquisitionDate()
{
    QString source  = textSegment().value("DATE").toString();
    return QDateTime::fromString(source,"dd-MMM-yyyy");
}

QList<QVariantList> FcsFile::dataSegment()
{

    int begin = dataBeginOffset();
    int end = dataEndOffset();
    int pCount = parameterCount();
    int total = eventCount();

    qDebug()<<begin<<" "<<end;

    seek(begin);
    QByteArray data = read(end-begin);
    QBuffer buffer;
       buffer.open(QBuffer::ReadWrite);

    QDataStream stream(data);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setVersion(QDataStream::Qt_4_8);

    int index = 0;
    QList<QVariantList> result;

    for ( int i=0; i<pCount; ++i)
        result.append(QVariantList());




        while (!stream.atEnd())
        {
           quint16 val = 0;
           stream >> val;
           result[index % pCount].append(val);
           ++index;




        }

    return result;





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

