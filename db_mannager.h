#ifndef DB_MANNAGER_H
#define DB_MANNAGER_H

#include <QSqlDatabase>

/**
 * \class DbManager
 *
 * \brief SQL Database Manager class
 *
 * DbManager sets up the connection with SQL database
 * and performs some basics queries. The class requires
 * existing SQL database. You can create it with sqlite:
 * 1. $ sqlite3 database.db
 * 2. sqilte> CREATE TABLE users(ids integer primary key, name text, password text);
 * 3. sqlite> .quit
 */
class DbManager
{
public:
    /**
     * @brief Constructor
     *
     * Constructor sets up connection with db and opens it
     * @param path - absolute path to db file
     */
    DbManager(const QString& path);

    /**
     * @brief Destructor
     *
     * Close the db connection
     */
    ~DbManager();

    bool isOpen() const;

    /**
     * @brief Creates a new 'user' table if it doesn't already exist
     * @return true - 'user' table created successfully, false - table not created
     */
    bool createTable();

    /**
     * @brief Add user data to db
     * @param name - name of user to add
     * @param password - password of user to add
     * @return true - person added successfully, false - person not added
     */
    bool addUser(const QString& name,const QString& password);

    /**
     * @brief Remove person data from db
     * @param name - name of person to remove.
     * @return true - person removed successfully, false - person not removed
     */
    bool removeUser(const QString& name);

    /**
     * @brief Check if person of name "name" exists in db
     * @param name - name of person to check.
     * @return true - person exists, false - person does not exist
     */
    bool userExists(const QString& name) const;

    /**
     * @brief Print names of all persons in db
     */
    void printAllUsers() const;

    /**
     * @brief Remove all persons from db
     * @return true - all persons removed successfully, false - not removed
     */
    bool removeAllUsers();

private:
    QSqlDatabase m_db;
};


#endif // DB_MANNAGER_H
