#ifndef USERS_H
#define USERS_H

#include <QMainWindow>
#include<QSpinBox>
#include<QLabel>

#include<QHBoxLayout>


namespace Ui {
class Users;
}

class Users : public QMainWindow
{
    Q_OBJECT

public:
    explicit Users(QWidget *parent = nullptr, QString ueamail="");
    ~Users();

    QList<QLabel*> costTracker;
    QList<QString> itemNameTracker;
    QList<QLabel *> totalTraker;
    QList<QSpinBox*> qtyTracker;

private slots:
    void on_pushButton_clicked();

    void on_homeButton_clicked();

    void on_orderButton_clicked();

    void on_myOrdersButton_clicked();

    void sayHi();

    void addItem(const QString& data);
    void removeItem(const QString& data);

    void on_spinBox_valueChanged(int arg1);
    void updateData();

    void on_confirmOrderButton_clicked();

private:
    Ui::Users *ui;
    QString uemail;

    void setUserProfileInfo(const QString& email);
    void setOrderList();
    void setMyOrdersList();
    QList<QList <QString>> getFromattedList(QString rawData);

    Users *users;

};

#endif // USERS_H
