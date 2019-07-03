#ifndef ORDER_DB_H
#define ORDER_DB_H

#include <QSqlDatabase>
#include <QList>

/**
  * In the order db we recodrs all the orders done by user
  * Create table with price per kg
  * User id -> unque user email from users data
  * Order date -> date when the order was placed
  * Order items -> its complex string itemName,qty,price
  * Order status -> Enum -> Ordered, Washing, Deliverded
*/

class Order_db
{
public:
    Order_db(const QString &path);

    bool isOpen() const;

    /**
     * Creates the table for the orders
     * order id is unique & auto increment
    */
    bool createTable()const;

    /**
     * Get all the the data from table
     * @return List of List of strings
    */
    QList<QList<QString>> getAllData() const;



    /**
      * Print all data to console
      * Just for debug purposes
    */
    void printAll();

    bool addItem(const QString& userEmail,const QString& orderDate, const QString& orders)const;

private:
    QSqlDatabase m_db;

};

#endif // ORDER_DB_H
