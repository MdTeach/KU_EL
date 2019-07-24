#ifndef DATETIMEFORMATTER_H
#define DATETIMEFORMATTER_H

#include<QString>
#include <QDebug>
#include <QDateTime>

class DateTimeFormatter
{
public:
    DateTimeFormatter();

    /**
      * Just retuns the unix seconds for the date string like Sun "Jul 21 2019 12:13:23"
    */
    uint getUnixTimeStamp(QString rawDate);
    QList<QList<uint>> sortByDate(QList<QString> dates, uint counter,QString latestDate);
    QList<QList<uint>> getArragnedDatas(QList<uint> dates, uint counter);

private:
    QString monthIndex(QString rawDate);
    QString getFormattedDate(QString rawDate);

};
#endif // DATETIMEFORMATTER_H
