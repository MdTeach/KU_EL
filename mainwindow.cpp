#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "identity.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Login_clicked()
{

    QString userName = ui -> lineEdit_userName->text();
    QString password = ui -> lineEdit_password->text();



    if (userName == "KUEL" && password == "ELforKU54"){
        QMessageBox :: information(this, "Login", "Welcome to admin secton.");
        hide();
        adminDialog = new AdminDialog(this);
        adminDialog -> show();
    }
    else if ((userName == "9813065709" || userName == "9869141635" || userName == "9866010823" || userName == "9861320161") && password == "test"){
        QMessageBox :: information (this, "Login", "Welcome to KUEL");
    }
    else{
        QMessageBox :: warning(this, "Login", "UserName or Password is incorrect.");
    }
}

void MainWindow::on_pushButton_Login_2_clicked()
{
    hide();
    userRegister = new UserRegister(this);
    userRegister->show();
}
