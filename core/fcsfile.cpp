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
#include "fcsfile.h"
#include <QByteArray>
#include <QDebug>
#include <QDataStream>
#include <QFile>

FcsFile::FcsFile(QObject *parent)
    :QFile(parent)
{
}

bool FcsFile::open()
{
    if(!QFile::open(QIODevice::ReadOnly)){
        qDebug()<<"cannot open file";
        return false;
    }

    if (!version().contains("FCS"))
    {
        qDebug()<<"This is not a FCS file";
        return false;
    }

    loadTextSegment();
    loadDataSegment();

    return true;
}

FcsFile::FcsFile(const QString &fileName, QObject *parent)
    :QFile(fileName,parent)
{



}


QString FcsFile::version()
{
    if (!isOpen())
        return QString();
    seek(0);
    return QString(read(6));
}


const QVariantMap& FcsFile::textSegment() const
{
    return mTextSegment;
}

QVector<double> FcsFile::dataSegment() const
{
    return mDataSegment;

}


FcsDataSource *  FcsFile::dataSource()
{

    QList<FcsField> fields;
    for (int col=1; col<=parameterCount(); ++col)
    {
        FcsField field;
        field.setName(textSegment().value(QString("P%1N").arg(col)).toString());
        field.setLabel(textSegment().value(QString("P%1S").arg(col)).toString());
        field.setGain(textSegment().value(QString("P%1G").arg(col)).toDouble());
        field.setRange(textSegment().value(QString("P%1R").arg(col)).toDouble());
        field.setVoltage(textSegment().value(QString("P%1V").arg(col)).toInt());
        fields.append(field);
    }

    mDataSource.setData(fields,mDataSegment);

    return &mDataSource;

}

FcsData FcsFile::data()
{
    FcsData fcsData;
    fcsData.setSource(dataSource());
    fcsData.selectAll();
    return fcsData;

}



//FcsData FcsFile::data()
//{
//    FcsData fcsData;
//    fcsData.setSource(dataSegment());
//    fcsData.setColumnCount(parameterCount());
//    for (int i=0; i<parameterCount(); ++i)
//        fcsData.setHeaderName(i,mTextSegment.value(QString("P%1N").arg(i+1)).toString());

//    fcsData.fill();
//    return fcsData;


//}





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

    seek(begin);
    QByteArray data = read(end-begin);


    QDataStream stream(data);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream.setVersion(QDataStream::Qt_4_8);

    int index = 0;
    mDataSegment.clear();

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

