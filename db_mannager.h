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
     * @param email - email of user to add. email is unique
     * @param password - password of user to add
     * @return true - person added successfully, false - person not added
     */
    bool addUser(const QString& email,const QString& password);

    /**
     * @brief Remove users data from db
     * @param email - email of user to remove.
     * @return true - user removed successfully, false - user not removed
     */
    bool removeUser(const QString& name);



    /**
     *@brief Check if the email is already taken
     */
    bool emailExists(const QString& email);


    void printAllUsers() const;

    /**
     * @brief Remove all users email from db
     * @return true - all users removed successfully, false - not removed
     */
    bool removeAllUsers();


    /**
     * @brief Authenticate the users via user email and password
     * @return db_primary_key - , 0 - log in failed
     */
    bool userAuth(const QString& name, const QString& pass) const;

private:
    QSqlDatabase m_db;
};


#endif // DB_MANNAGER_H
