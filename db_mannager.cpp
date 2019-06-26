#include <db_mannager.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

DbManager::DbManager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open()){
        qDebug() << "Error: connection with database fail";
    }else{
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
    query.prepare("CREATE TABLE user(id INTEGER PRIMARY KEY, email TEXT,pass TEXT, fname TEXT, lname TEXT, addr TEXT, phn TEXT);");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'user': one might already exist.";
        success = false;
    }

    return success;
}

bool DbManager::addUser(const QString &email, const QString &pass, const QString &fname, const QString &lname, const QString &addr, const QString &phn){
    bool success = false;
    QSqlQuery queryAdd;
    queryAdd.prepare("INSERT INTO user(email, pass, fname, lname, addr, phn) VALUES (:email, :pass, :fname, :lname, :addr, :phn)");
    queryAdd.bindValue(":email", email);
    queryAdd.bindValue(":pass", pass);
    queryAdd.bindValue(":fname",fname);
    queryAdd.bindValue(":lname",lname);
    queryAdd.bindValue(":addr",addr);
    queryAdd.bindValue(":phn",phn);

    if(!queryAdd.exec()){
        qDebug() << "add user failed: " << queryAdd.lastError();
    }else{
        success = true;
    }
    return success;
}



bool DbManager::removeUser(const QString& name){
    bool success = false;

    if (emailExists(name)){
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM people WHERE name = (:name)");
        queryDelete.bindValue(":name", name);
        success = queryDelete.exec();
        if(!success){
            qDebug() << "remove  failed: " << queryDelete.lastError();
        }
    }else{
        qDebug() << "remove user failed: user doesnt exist";
    }
    return success;
}

void DbManager::printAllUsers() const{
    qDebug() << "users in db:";
    QSqlQuery query("SELECT * FROM user");
    int idName = query.record().indexOf("email");
    while (query.next())
    {
        QString email = query.value(idName).toString();
        qDebug() << "===" << email;
    }
}



bool DbManager::emailExists(const QString &email){
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT email FROM user WHERE email = (:email)");
    checkQuery.bindValue(":email",email);
    if(checkQuery.exec()){
        if(checkQuery.next()){
            return true;
        }
    }else{
        qDebug()<<"does email exist query failed "<<checkQuery.lastError();
    }
    return false;
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

bool DbManager::userAuth(const QString &email, const QString &pass)const{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT email FROM user WHERE email = (:email) AND pass = (:pass)");
    checkQuery.bindValue(":email", email);
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

QList<QString> DbManager::getAllUsers() const{
    QList<QString> userList;

    qDebug() << "users in db:";
    QSqlQuery query("SELECT * FROM user");
    int idName = query.record().indexOf("email");
    while (query.next()){
        QString email = query.value(idName).toString();
        userList.push_front(email);
    }

    return  userList;
}

