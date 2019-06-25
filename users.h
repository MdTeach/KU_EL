#ifndef USERS_H
#define USERS_H

#include <QMainWindow>

namespace Ui {
class Users;
}

class Users : public QMainWindow
{
    Q_OBJECT

public:
    explicit Users(QWidget *parent = nullptr);
    ~Users();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Users *ui;
};

#endif // USERS_H
