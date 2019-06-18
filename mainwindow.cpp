#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "identity.h"

#include <QDebug>
#include <db_mannager.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DbManager db("database.db");
    if(!db.isOpen()){
        qDebug()<<"Database not opening";
    }else{
        db.createTable();   // Creates a table if it doens't exist. Otherwise, it will use existing table.
        db.printAllUsers();
    }
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_pushButton_Login_clicked()
{

    QString userName = ui -> lineEdit_userName->text();
    QString password = ui -> lineEdit_password->text();

    DbManager db("database.db");
    bool succ = db.userAuth(userName,password);
    qDebug()<<succ;
    if(!succ){
        //login failed show error message
        QMessageBox :: information (this, "Error!!", "Worng username or password");
    }else{
        hide();
        adminDialog = new AdminDialog(this);
        adminDialog->show();
    }


}

void MainWindow::on_pushButton_Login_2_clicked()
{
    hide();
    userRegister = new UserRegister(this);
    userRegister->show();
}
