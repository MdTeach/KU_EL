#include "admin.h"
#include "ui_admin.h"

#include<QDebug>

#include <db_mannager.h>
#include <admin_db.h>

#include <QList>

Admin::Admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);

    //Adding the list of users
    addUserList();

    //Adding items to the list
    addItemList();


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
    ui->stackedWidget->setCurrentIndex(2);
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

void Admin::addItemList(){
    Admin_db admin_db("database.db");
    admin_db.printAll();

    QList<QList<QString>> data = admin_db.getAllData();

    QString spacing = "    "; //1 tab

    QLabel* haderLabel = new QLabel();
    haderLabel->setText("SN"+spacing+"Item Name"+spacing+"Price");
    //ui->itemsList->addWidget(haderLabel);

    for(int i=0;i<data.length();i++){
        QList<QString> temp = data[i];
        QString itemName = temp[0];
        QString itemCost = temp[1];

        QLabel *item = new QLabel();
        QString text = QString::number(i+1)+spacing+itemName+spacing+itemCost;
        item->setText(text);
        ui->itemsList->addWidget(item);

    }



}


void Admin::on_listOrderButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Admin::on_addDataButton_clicked()
{
    //Adding item to the db
    Admin_db admin_db("database.db");
    admin_db.createTable();

    QString itemName = ui->addItemName->text();
    QString itemCost = ui->addRate->text();

    if( isEmpty(itemName) && isEmpty(itemCost)){
        //Show err
        qDebug()<<"Provide all the credientials";
    }else{
        if(admin_db.doesItemExits(itemName)){
            //Item already exist
            qDebug()<<"Item already exists";
        }else{
            admin_db.addItem(itemName,itemCost);

        }
    }


}

bool Admin::isEmpty(const QString& str)const{
    if(str == "" || str == " ") return true;
    return false;
}
