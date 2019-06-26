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

    //Gets all data from the db
    QList<QList<QString>> data = admin_db.getAllData();

    //Spacing between SN and Item name column
    QString spacing = "     "; //1 tab

    //Setting text label for the table header
    QLabel* haderNameLabel = new QLabel();
    QLabel* haderPriceLabel = new QLabel();

    //Setting data to table headers
    haderNameLabel->setText("SN"+spacing+"Item Name");
    haderPriceLabel->setText("Price");

    //Inserting the header label to the UI
    ui->itemsList->addWidget(haderNameLabel);
    ui->itemPirceList->addWidget(haderPriceLabel);

    //Loopig through all data and showing in the VLayout
    for(int i=0;i<data.length();i++){
        QList<QString> temp = data[i];
        QString itemName = temp[0];
        QString itemCost = temp[1];

        QLabel *itemNameLabel = new QLabel();
        QLabel *itemPriceLabel = new QLabel();

        QString nameString = QString::number(i+1)+spacing+spacing+itemName;
        QString costString = itemCost;

        itemNameLabel->setText(nameString);
        itemPriceLabel->setText(costString);

        ui->itemsList->addWidget(itemNameLabel);
        ui->itemPirceList->addWidget(itemPriceLabel);
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

            this->close();
            QWidget *parent = this->parentWidget();
            parent->show();
        }
    }


}

bool Admin::isEmpty(const QString& str)const{
    if(str == "" || str == " ") return true;
    return false;
}

void Admin::on_reoveItemButton_clicked()
{
    //Remove the list content
    QString itemName = ui->removeItemName->text();
    if(isEmpty(itemName)){
        qDebug("the item is empty. provide the valid name");
    }else{
        Admin_db admin_db("database.db");
        if(!admin_db.doesItemExits(itemName)){
            //Item donot exist show message
            qDebug()<<"Given Item doesn't exist";
        }else{
            //remove the data
            admin_db.removeItem(itemName);

            this->close();
            QWidget *parent = this->parentWidget();
            parent->show();
        }
    }


}
