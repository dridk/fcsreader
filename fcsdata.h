#ifndef FCSDATA_H
#define FCSDATA_H
#include <QVariantList>
class FcsData : public QList<int>
{
public:
    FcsData();
    double valueAtCoord(int row, int column) const;
    void appendRow(int row);
    void setColumnCount(int count);

    int rowCount() const;
    int columnCount() const;

    void clear() {QList<int>::clear(); mRowCount = 0;}

    void fill();

     QString headerName(int column) const;
    void setHeaderName(int column, const QString& name);
    void setSource( QVector<double> * source);
    QVector<double>* source() const {return mSource;}


private:
    int mRowCount;
    int mColumnCount;
    QMap<int,QString> mHeaders;
    QVector<double> * mSource;
};

#endif // FCSDATA_H
