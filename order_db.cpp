#include "order_db.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

Order_db::Order_db(const QString &path){
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open()){
        qDebug() << "Error: connection with database fail";
    }else{
        qDebug() << "Database: connection ok";
    }
}

bool Order_db::isOpen() const{
    return this->m_db.isOpen();
}

bool Order_db::createTable() const{
    QSqlQuery createQuery;
    createQuery.prepare("CREATE TABLE orders(id INTEGER PRIMARY KEY, userEmail TEXT,orderDate TEXT, orderList TEXT, orderStatus TEXT);");
    if(createQuery.exec()){
        return true;
    }else{
        qDebug()<<createQuery.lastError();
        return false;
    }
}

bool Order_db::addItem(const QString &userEmail, const QString &orderDate, const QString &orders) const{
    QSqlQuery addQuery;
    QString orderStatus = "Ordered";

    addQuery.prepare("INSERT INTO orders(userEmail,orderDate,orderList,orderStatus) VALUES(:userEmail, :orderDate, :orderList, :orderStatus)");
    addQuery.bindValue(":userEmail",userEmail);
    addQuery.bindValue(":orderDate",orderDate);
    addQuery.bindValue(":orderList",orders);
    addQuery.bindValue(":orderStatus",orderStatus);

    if(!addQuery.exec()){
        qDebug()<<addQuery.lastError();
        return  false;
    }else{
        return  true;
    }
}



