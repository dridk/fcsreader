#ifndef FCSDATA_H
#define FCSDATA_H
#include <QVariantList>
class FcsData
{
public:
    FcsData();
    double value(int row, int column) const;
    void setRowCount(int count);
    void setColumnCount(int count);

    int rowCount() const;
    int columnCount() const;
    int size() const;

    void fill();

    const QString& headerName(int column) const;
    void setHeaderName(int column, const QString& name);
    void setSource(QVector<double> * source);


private:
    int mRowCount;
    int mColumnCount;
    QMap<int,QString> mHeaders;
    QList<int> mIds;
    QVector<double> * mSource;
};

#endif // FCSDATA_H
