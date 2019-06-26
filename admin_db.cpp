#include "admin_db.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>


Admin_db::Admin_db(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open()){
        qDebug() << "Error: connection with database fail";
    }else{
        qDebug() << "Database: connection ok";
    }
}

bool Admin_db::isOpen()const{
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

bool Admin_db::addItem(const QString &itemName, const QString &price) const{
    bool success = false;
    QSqlQuery queryAdd;
    queryAdd.prepare("INSERT INTO item(itemName, price) VALUES (:itemName, :price)");
    queryAdd.bindValue(":itemName", itemName);
     queryAdd.bindValue(":price", price);
    if(!queryAdd.exec()){
        qDebug() << "add item failed: " << queryAdd.lastError();
    }else{
        success = true;
    }
    return success;
}


