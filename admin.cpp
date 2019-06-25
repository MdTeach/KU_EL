#include "admin.h"
#include "ui_admin.h"

#include<QDebug>
#include <db_mannager.h>
#include <QList>

Admin::Admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);

    addUserList();
}

Admin::~Admin()
{
    delete ui;
}

void Admin::on_pushButton_clicked()
{
    this->close();
    QWidget *parent = this->parentWidget();
    parent->show();
}



void Admin::on_listOrderButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}


void Admin::on_listUserButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void Admin::addUserList(){
    DbManager db("database.db");
    QList<QString> data = db.getAllUsers();
    qDebug()<<data[0];

    for(int i=0; i<data.length();i++){
        QLabel *item = new QLabel();
        QString text = QString::number((i+1))+") "+data[i];
        item->setText(text);
        ui->userLayout->addWidget(item);
    }
}

