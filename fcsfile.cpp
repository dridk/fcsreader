#include "fcsfile.h"
#include <QByteArray>
#include <QDebug>
#include <QDataStream>

FcsFile::FcsFile(QObject *parent)
    :QFile(parent)
{

}

FcsFile::FcsFile(const QString &fileName, QObject *parent)
    :QFile(fileName,parent)
{
}
FcsFile::~FcsFile()
{

}



const QVariantMap& FcsFile::textSegment() const
{
    return mTextSegment;
}

QVector<double>* FcsFile::dataSegment()
{

    return &mDataSegment;
}

FcsData FcsFile::data()
{
    FcsData fcsData;
    fcsData.setSource(dataSegment());
    fcsData.setColumnCount(parameterCount());
    for (int i=0; i<parameterCount(); ++i)
        fcsData.setHeaderName(i,mTextSegment.value(QString("P%1N").arg(i+1)).toString());

    fcsData.fill();
    return fcsData;


}

void FcsFile::load()
{
    loadTextSegment();
    loadDataSegment();


}

void FcsFile::test()
{

}

int FcsFile::parameterCount() const
{
    return mTextSegment.value("PAR").toInt();
}

int FcsFile::eventCount() const
{
    return mTextSegment.value("TOT").toInt();
}

QDateTime FcsFile::aquisitionDate() const
{
    QString source  = mTextSegment.value("DATE").toString();
    return QDateTime::fromString(source,"dd-MMM-yyyy");
}

QString FcsFile::version()
{
    if (!isOpen())
        return QString();
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

void FcsFile::loadTextSegment()
{
    if (!isOpen())
        return;
    int begin = textBeginOffset();
    int end = textEndOffset();
    seek(begin);
    QString textData = QString::fromAscii(read(end-begin));
    mTextSegment.clear();
    foreach (QString pair, textData.split(QRegExp("\\$|@")))
    {
        pair = pair.remove(pair.length()-1,1); //remove last slash

        QStringList pairList= pair.split(QRegExp("\\\\{1}"));
        QString key = pairList.first();
        QVariant value = pairList.length() > 1 ? pairList.at(1) : 0;
        mTextSegment.insert(key,value);
    }
}

void FcsFile::loadDataSegment()
{
    if (!isOpen())
        return;

    int begin = dataBeginOffset();
    int end = dataEndOffset();
    int pCount = parameterCount();
    int total = eventCount();



    seek(begin);
    QByteArray data = read(end-begin);


    QDataStream stream(data);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setVersion(QDataStream::Qt_4_8);

    int index = 0;
    mDataSegment.clear();
    //    mDataSegment.setRowCount(total);
    //    mDataSegment.setColumnCount(pCount);



    while (!stream.atEnd())
    {
        int pId = (index % pCount)+1;
        int byte = mTextSegment.value(QString("P%1B").arg(pId)).toInt();

        QVariant value;
        if (byte == 16){
            quint16 val = 0;
            stream >> val;
            value = val;
        }
        if (byte == 32){
            quint32 val = 0;
            stream >> val;
            value = val;
        }

        if (byte == 64){
            quint64 val = 0;
            stream >> val;
            value = val;
        }

        mDataSegment.append(value.toDouble());
        ++index;
    }


}

