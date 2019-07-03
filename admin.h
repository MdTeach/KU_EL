#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include <QList>
namespace Ui {
class Admin;
}

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();

private slots:
    void on_logoutButton_clicked();

    void on_listOrdersButton_clicked();

    void on_listItemsButton_clicked();

    void on_listUsersButton_clicked();

    void on_addDataButton_clicked();

    void on_reoveItemButton_clicked();

private:
    Ui::Admin *ui;
    void addUserList();
    void addItemList();
    void addOrderList();
    QList<QList<QString>> getFormattedList(QString rawData);
    bool isEmpty(const QString& str)const;
};

#endif // ADMIN_H
