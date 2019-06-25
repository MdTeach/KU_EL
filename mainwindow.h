#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <admindialog.h>
#include <userregister.h>

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

private slots:
    void on_pushButton_Login_clicked();

    void on_pushButton_Login_2_clicked();

    void on_homeButton_clicked();

    void on_loginButton_clicked();

    void on_registerButton_clicked();

    void on_aboutButton_clicked();

private:
    Ui::MainWindow *ui;
    AdminDialog *adminDialog;
    UserRegister *userRegister;
};

#endif // MAINWINDOW_H
