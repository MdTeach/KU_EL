#include "admin.h"
#include "ui_admin.h"

#include<QDebug>

#include <db_mannager.h>
#include <admin_db.h>
#include<order_db.h>

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

    //Adding item to users orders
    addOrderList();


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

    for(int i=0; i<data.length();i++){
        QLabel *item = new QLabel();
        QString text = QString::number((i+1))+") "+data[i];
        item->setText(text);
        ui->userLayout->addWidget(item);
    }
}

void Admin::addOrderList(){
    Order_db order_db("database.db");
    QList<QList<QString>> datas = order_db.getAllData();

    //Working with the raw data
    QVBoxLayout* parentHbox = new QVBoxLayout(); //= new QVBoxLayout();
    for(int i=0;i<datas.length();i++){
        QVBoxLayout* hbox = new QVBoxLayout();

        QList<QString> data = datas[i];
        qDebug()<<data[0];
        qDebug()<<data[1];
        qDebug()<<data[2];
        qDebug()<<data[3];

        QLabel* userEmail = new QLabel();
        QLabel* orderDate = new QLabel();
        QLabel* orderStatus = new QLabel();

        userEmail->setText("User Email "+data[0]);
        orderDate->setText("Orderd on "+data[1]);
        orderStatus->setText("Order status: "+data[3]);

        QList<QList <QString>> qlist_data = getFromattedList(data[2]);

        QLabel* oder_num = new QLabel();
        oder_num->setText("Order no " + QString::number(i+1));
        hbox->addWidget(oder_num);

        hbox->addWidget(userEmail);
        hbox->addWidget(orderDate);
        QLabel* br = new QLabel();
        hbox->addWidget(br);


        //Adding ordered items
        for(int i=0;i<qlist_data.length();i++){
            QList<QString> list_of_orders_string = qlist_data[i];
            for(int j=0;j<list_of_orders_string.length();j++){
                QLabel* order_item_label = new QLabel();
                order_item_label->setText(list_of_orders_string[j]);
                hbox->addWidget(order_item_label);
            }
            hbox->addWidget(br);
        }


        hbox->addWidget(orderStatus);
        QPushButton* deleteButton = new QPushButton();
        deleteButton->setText("Delete");

        hbox->addWidget(deleteButton);
        hbox->addWidget(br);
        hbox->setMargin(12);

        parentHbox->addItem(hbox);
    }
    //ui->viewOrderList->setLayout(parentHbox);
    ui->scrollAreaWidgetContents->setLayout(parentHbox);
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

QList<QList <QString>> Admin::getFromattedList(QString rawData){
    QList<QList<QString>> data;
    QStringList orders = rawData.split('>');
    for(int i=0;i<orders.length()-1;i++){
        QList<QString> list_of_orders_string;
        QStringList order = orders[i].split('.');
        //itemName ->0
        list_of_orders_string.push_back("Item Name: "+order[0]);
        //itemQTy ->1
        list_of_orders_string.push_back("Qty: "+order[1]);
        //itemRate->2
        list_of_orders_string.push_back("Item Rate: Rs "+order[2]);
        data.push_front(list_of_orders_string);
    }
    return data;
}
