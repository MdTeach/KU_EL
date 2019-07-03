#ifndef DB_MANNAGER_H
#define DB_MANNAGER_H

#include <QSqlDatabase>
#include<QList>

class DbManager
{
public:

    DbManager(const QString& path);

    ~DbManager();

    bool isOpen() const;

    bool createTable();

    bool addUser(const QString& email,const QString& password,const QString& fname,const QString& lname,const QString& addr,const QString& phn);

    bool removeUser(const QString& name);

    bool emailExists(const QString& email);

    bool removeAllUsers();

    bool userAuth(const QString& name, const QString& pass) const;

    QList<QString> getUserInfo(const QString& email)const;

    QList<QString> getAllUsers();

private:
    QSqlDatabase m_db;
};


#endif // DB_MANNAGER_H
