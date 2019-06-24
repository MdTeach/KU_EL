#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <admindialog.h>
#include <userregister.h>

#include <QtSql>
#include <QDebug>
#include <QFileInfo>

#include<home.h>
#include<user.h>
#include<admin.h>


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

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Home *homeStack;
    admin *adminStack;
    User *userStack;
//    AdminDialog *adminDialog;
//    UserRegister *userRegister;
};

#endif // MAINWINDOW_H
