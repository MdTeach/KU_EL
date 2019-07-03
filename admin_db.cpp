#include "admin_db.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QList>


Admin_db::Admin_db(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open()) {
        qDebug() << "Error: connection with database fail";
    } else {
        qDebug() << "Database: connection ok";
    }
}

bool Admin_db::isOpen()const {
    return this->m_db.isOpen();
}

bool Admin_db::createTable() const{

    QSqlQuery query;
    query.prepare("CREATE TABLE item(id INTEGER PRIMARY KEY, itemName TEXT,cost TEXT);");
    if(query.exec()){
        return true;
    }else{
        qDebug() << "Couldn't create the table 'user': one might already exist.";
        return false;
    }
}

bool Admin_db::doesItemExits(const QString &itemName) const{
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT itemName FROM item WHERE itemName = (:itemName)");
    checkQuery.bindValue(":itemName",itemName);
    if(checkQuery.exec()){
        if(checkQuery.next()){
            return true;
        }
    }else{
        qDebug()<<"does item exist query failed "<<checkQuery.lastError();
    }
    return false;
}

bool Admin_db::removeItem(const QString &itemName) const{
    bool success = false;

    if (doesItemExits(itemName)){
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM item WHERE itemName = (:itemName)");
        queryDelete.bindValue(":itemName", itemName);
        success = queryDelete.exec();
        if(!success){
            qDebug() << "remove  failed: " << queryDelete.lastError();
        }
    }else{
        qDebug() << "remove user failed: item doesnt exist";
    }
    return success;
}

void Admin_db::printAll(){
    qDebug() << "items in in db:";
    QSqlQuery query("SELECT * FROM item");
    int idName = query.record().indexOf("itemName");
    while (query.next()){
        QString name = query.value(idName).toString();
        qDebug() << "===" << name;
    }
}

bool Admin_db::addItem(const QString &itemName, const QString &cost) const{
    bool success = false;
    QSqlQuery queryAdd;
    queryAdd.prepare("INSERT INTO item(itemName, cost) VALUES (:itemName, :cost)");
    queryAdd.bindValue(":itemName", itemName);
     queryAdd.bindValue(":cost", cost);
    if(!queryAdd.exec()){
        qDebug() << "add item failed: " << queryAdd.lastError();
    }else{
        success = true;
    }
    return success;
}

QList<QList<QString>> Admin_db::getAllData()const{
    QSqlQuery query("SELECT * FROM item");

    int itemName_id = query.record().indexOf("itemName");
    int cost_id = query.record().indexOf("cost");

    QList<QList<QString>> data;
    while (query.next()){
        QList<QString> list;

        QString itemName = query.value(itemName_id).toString();
        QString cost = query.value(cost_id).toString();

        list.push_front(cost);
        list.push_front(itemName);

        data.push_front(list);
    }
    return data;
}

