#ifndef ORDER_DB_H
#define ORDER_DB_H

#include <QSqlDatabase>
#include <QList>

class Order_db
{
public:
    Order_db(const QString &path);
    bool isOpen() const;
    bool createTable()const;
    QList<QList<QString>> getAllData() const;
    void printAll();
    bool addItem(const QString& userEmail,const QString& orderDate, const QString& orders)const;
    QList<QList<QString>> getUserData(QString uemail);

private:
    QSqlDatabase m_db;
    QList<QList<QString>> getUserOrdersData(QString uemail);
};

#endif // ORDER_DB_H
