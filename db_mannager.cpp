#include <db_mannager.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

DbManager::DbManager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

DbManager::~DbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool DbManager::isOpen() const
{
    return m_db.isOpen();
}

bool DbManager::createTable()
{
    bool success = false;

    QSqlQuery query;
    query.prepare("CREATE TABLE user(id INTEGER PRIMARY KEY, name TEXT,pass TEXT);");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'user': one might already exist.";
        success = false;
    }

    return success;
}

bool DbManager::addUser(const QString& name, const QString& pass)
{
    bool success = false;

    if (!name.isEmpty())
    {
        QSqlQuery queryAdd;
        queryAdd.prepare("INSERT INTO user(name, pass) VALUES (:name, :pass)");
        queryAdd.bindValue(":name", name);
         queryAdd.bindValue(":pass", pass);
        if(queryAdd.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "add user failed: " << queryAdd.lastError();
        }
    }
    else
    {
        qDebug() << "add user failed: name cannot be empty";
    }

    return success;
}

bool DbManager::removeUser(const QString& name)
{
    bool success = false;

    if (userExists(name))
    {
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM people WHERE name = (:name)");
        queryDelete.bindValue(":name", name);
        success = queryDelete.exec();

        if(!success)
        {
            qDebug() << "remove  failed: " << queryDelete.lastError();
        }
    }
    else
    {
        qDebug() << "remove user failed: user doesnt exist";
    }

    return success;
}

void DbManager::printAllUsers() const
{
    qDebug() << "users in db:";
    QSqlQuery query("SELECT * FROM user");
    int idName = query.record().indexOf("name");
    while (query.next())
    {
        QString name = query.value(idName).toString();
        qDebug() << "===" << name;
    }
}

bool DbManager::userExists(const QString& name) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT name FROM user WHERE name = (:name)");
    checkQuery.bindValue(":name", name);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "user exists failed: " << checkQuery.lastError();
    }

    return exists;
}

bool DbManager::removeAllUsers()
{
    bool success = false;

    QSqlQuery removeQuery;
    removeQuery.prepare("DELETE FROM user");

    if (removeQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "remove all users failed: " << removeQuery.lastError();
    }

    return success;
}

bool DbManager::userAuth(const QString &name, const QString &pass)const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT name FROM user WHERE name = (:name) AND pass = (:pass)");
    checkQuery.bindValue(":name", name);
    checkQuery.bindValue(":pass", pass);
    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "user exists failed: " << checkQuery.lastError();
    }

    return exists;
}


