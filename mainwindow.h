#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>


#include<users.h>
#include<admin.h>

#include <QtSql>
#include <QDebug>
#include <QFileInfo>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showMessage(MainWindow* context, const QString message);

private slots:
    void on_pushButton_Login_clicked();

    void on_homeButton_clicked();

    void on_loginButton_clicked();

    void on_registerButton_clicked();

    void on_aboutButton_clicked();

    void on_adminButton_clicked();

    void on_userButton_clicked();

    void on_registerButton_2_clicked();

private:
    Ui::MainWindow *ui;

    Users *users;
    Admin *admin;
};

#endif // MAINWINDOW_H
