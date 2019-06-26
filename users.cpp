#include "users.h"
#include "ui_users.h"

#include<QDebug>

Users::Users(QWidget *parent,QString uemail) :
    QMainWindow(parent),
    ui(new Ui::Users)
{
    ui->setupUi(this);
    this->uemail = uemail;

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
