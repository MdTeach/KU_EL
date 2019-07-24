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
    void on_pushButton_clicked();

    void on_listOrderButton_clicked();

    void on_listUserButton_clicked();

    void on_listOrderButton_2_clicked();

    void on_addDataButton_clicked();

    void on_reoveItemButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Admin *ui;
    void addUserList();
    void addItemList();
    void addOrderList();

    void showAnalitics();
    QList<QList<QString>> getFromattedList(QString rawData);
    bool isEmpty(const QString& str)const;
};

#endif // ADMIN_H
