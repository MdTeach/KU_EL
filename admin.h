#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>

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

private:
    Ui::Admin *ui;
    void addUserList();
    void addItemList();
    bool isEmpty(const QString& str)const;
};

#endif // ADMIN_H
