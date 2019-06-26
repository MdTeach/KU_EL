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


