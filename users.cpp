#include "users.h"
#include "ui_users.h"

#include<QDebug>

Users::Users(QWidget *parent,QString uemail) :
    QMainWindow(parent),
    ui(new Ui::Users)
{
    ui->setupUi(this);
    this->uemail = uemail;
    this->setWindowTitle("User");
    //Home page setup
    ui->userStack->setCurrentIndex(0);
    QString msg = "Hello "+this->uemail;
    ui->greetLabel->setText(msg);

}

Users::~Users()
{
    delete ui;
}

void Users::on_pushButton_clicked()
{
    this->close();
    QWidget *parent = this->parentWidget();
    parent->show();
}

void Users::on_homeButton_clicked()
{
    ui->userStack->setCurrentIndex(0);
}

void Users::on_orderButton_clicked()
{
    ui->userStack->setCurrentIndex(1);
}

void Users::on_myOrdersButton_clicked()
{
    ui->userStack->setCurrentIndex(2);
}
