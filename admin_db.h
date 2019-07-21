#ifndef ADMIN_DB_H
#define ADMIN_DB_H

#include <QSqlDatabase>
#include <QList>

/**
  * As admin I should be able to set the charge per KG
  * Create table with price per kg
  *
*/

class Admin_db
{
public:
    Admin_db(const QString &path);

    bool isOpen() const;
    bool createTable()const;
    QList<QList<QString>> getAllData() const;
    bool doesItemExits(const QString& itemName)const;
    bool removeItem(const QString& itemName)const;
    void printAll();
    bool upDatePrice(const QString& itemName,const QString& newPrice)const;
    bool addItem(const QString& itemName,const QString& cost)const;

private:
    QSqlDatabase m_db;
};



#endif // ADMIN_DB_H
