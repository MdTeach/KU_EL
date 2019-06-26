#include "users.h"
#include "ui_users.h"

#include<QDebug>
#include<QList>

#include<db_mannager.h>
#include<admin_db.h>

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

    setUserProfileInfo(uemail);

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

void Users::setUserProfileInfo(const QString& email){
    DbManager db("database.db");
    QList<QString> data = db.getUserInfo(email);

    qDebug()<<"Hello SId";

    QString uEmail = data[0];
    QString uFname = data[1];
    QString uLname = data[2];
    QString uAddr = data[3];
    QString uPhn = data[4];

    ui->greetLabel->setText("Welcome "+uFname);
    ui->emailLabel->setText("Email: "+uEmail);
    ui->phoneLabel->setText("Phn: "+uPhn);
    ui->addressLabel->setText("Addrs: "+uAddr);

}
