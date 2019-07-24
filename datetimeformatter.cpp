#include "datetimeformatter.h"

DateTimeFormatter::DateTimeFormatter()
{

}

QString DateTimeFormatter::monthIndex(QString rawDate){
    if(rawDate == "Jan") return "1";
    if(rawDate == "Feb") return "2";
    if(rawDate == "Mar") return "3";
    if(rawDate == "Apr") return "4";
    if(rawDate == "May") return "5";
    if(rawDate == "Jun") return "6";
    if(rawDate == "Jul") return "7";
    if(rawDate == "Aug") return "8";
    if(rawDate == "Sep") return "9";
    if(rawDate == "Oct") return "10";
    if(rawDate == "Nov") return "11";
    return "12";
}

QString DateTimeFormatter::getFormattedDate(QString rawDate){
    QStringList pieces = rawDate.split( " " );
    QString formattedDate = "M"+monthIndex(pieces[1])+"d"+pieces[2]+"y"+pieces[3]+" "+pieces[5];
    QDateTime dateTime2 = QDateTime::fromString(formattedDate,"'M'M'd'd'y'yyyy hh:mm:ss");
    return  formattedDate;
}

uint DateTimeFormatter::getUnixTimeStamp(QString rawDate){
    QDateTime dateTime2 = QDateTime::fromString(getFormattedDate(rawDate),"'M'M'd'd'y'yyyy hh:mm:ss");
    uint unixtime = dateTime2.toTime_t();
    return  unixtime;
}

QList<QList<uint>> DateTimeFormatter::sortByDate(QList<QString> dates, uint counter){
    uint latest = getUnixTimeStamp(dates[0]);
    QList<uint> lastMinutesDatas;
    for(int i=0;i<dates.length();i++){
        uint times = getUnixTimeStamp(dates[i]);
            if(times <= latest+counter){
                lastMinutesDatas.append(times);
            }
    }
    return getArragnedDatas(lastMinutesDatas,counter);
}


QList<QList<uint>> DateTimeFormatter::getArragnedDatas(QList<uint> datas, uint separation){
    QList<QList<uint>> arranged_datas = QList<QList<uint>>();
    int index = 0;
    uint phase = datas[0]+separation/60;
    while(true){
        QList<uint> same_data = {};
        for (int i=index;i<datas.length();i++){
            if(double(phase)-double(datas[i])>0){
                same_data.append(datas[i]);
            }else{
                phase+=separation/60;
                break;
            }
            index+=1;
        }
        if(same_data.length()>0){
          arranged_datas.append(same_data);
        }
        if(index >= datas.length()){
            break;
        }
    }
    return arranged_datas;
}
