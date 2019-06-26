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

    /**
     * Creates the table of the the item
     * itemName is unique
    */
    bool createTable()const;

    /**
     * Get all the the data from table
     * @return List of List of strings
    */
    QList<QList<QString>> getAllData() const;

    /**
      * Check if the item exist
      * @param itemName String unique in db
      * @return true if exist
    */
    bool doesItemExits(const QString& itemName)const;

    /**
      * Remove the item from the db
      * @param itemName String unique in db
      * @return true if worked sucessfully
    */
    bool removeItem(const QString& itemName)const;

    /**
      * Print all data to console
      * Just for debug purposes
    */
    void printAll();


    /**
      * Update the price of the item
      * @param itemName -> unique in db
      * @param newPrice -> price to be set
      * @return true if worked sucessfully
    */
    bool upDatePrice(const QString& itemName,const QString& newPrice)const;

    /**
      * Adding data to db
      * @param itemName -> unique in db
      * @param Price -> price to be set
      * @return true if worked sucessfully
    */
    bool addItem(const QString& itemName,const QString& cost)const;


private:
    QSqlDatabase m_db;

};



#endif // ADMIN_DB_H
