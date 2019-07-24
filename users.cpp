#include "users.h"
#include "ui_users.h"

#include<QDebug>
#include<QList>
#include<QHBoxLayout>
#include<db_mannager.h>
#include<admin_db.h>
#include<order_db.h>

#include <QDate>

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

    //Set user profile
    setUserProfileInfo(uemail);

    //Set order page
    setOrderList();

    //Set my orders
    setMyOrdersList();

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

void Users::setOrderList(){
    Admin_db admin_db("database.db");
    QList<QList<QString>> data = admin_db.getAllData();

    for(int i=0;i<data.length();i++){
        QList<QString> itemData = data[i];

        QSpinBox* spinBox = new QSpinBox();
        QLabel* itemNameLabel = new QLabel();
        QLabel* priceLabel = new QLabel();
        QLabel* totalPriceLabel = new QLabel();

        // Note: 0->itemName 1->itemCost
        itemNameLabel->setText(itemData[0]);
        priceLabel->setText(itemData[1]);

        totalPriceLabel->setText("Rs 0");
        QString itemName = itemData[0];

        spinBox->setObjectName(itemName+"box");
        qtyTracker.append(spinBox);
        totalTraker.append(totalPriceLabel);
        costTracker.append(priceLabel);
        itemNameTracker.append(itemName);

        connect(spinBox, SIGNAL(valueChanged(int)),SLOT(updateData()));

        ui->itemName->addWidget(itemNameLabel);
        ui->itemPrice->addWidget(priceLabel);
        ui->itemQty->addWidget(spinBox);
        ui->itemAdd->addWidget(totalPriceLabel);\
    }
}

void Users::sayHi(){
    qDebug()<<"was clicked";
}

void Users::addItem(const QString& data){
    qDebug()<<"Add "+data;
}

void Users::removeItem(const QString& data){
    qDebug();
    qDebug()<<"Delete "+data;
}

void Users::updateData(){
    int grandTot = 0;
    for(int i=0;i<qtyTracker.length();i++){
        QLabel* rate = costTracker[i];
        QLabel* totalPrice = totalTraker[i];
        QSpinBox* spinBox = qtyTracker[i];

        int sumationPrice = rate->text().toInt() * spinBox->text().toInt();
        grandTot += sumationPrice;

        qDebug()<<rate->text()<<spinBox->text();
        totalPrice->setText(QString::number(sumationPrice));
    }
    ui->grandTotalLabel->setText(QString::number(grandTot));

}

void Users::on_spinBox_valueChanged(int arg1)
{

}

void Users::on_confirmOrderButton_clicked()
{
    if(ui->grandTotalLabel->text() ==  "0"){
    }else{
        //Preparing data
        QString userEmail = this->uemail;
        QString qDate = QDate::currentDate().toString();
        QString qTime = QTime::currentTime().toString();
        qDate = qDate + " at " + qTime;
        //qDebug() << concatinated;
        QString orders;

        for(int i=0; i<this->qtyTracker.length();i++){
            QLabel* rate = costTracker[i];
            QSpinBox* spinBox = qtyTracker[i];

            QString rateStr = rate->text();
            QString qtyStr = spinBox->text();
            QString itemNameStr = itemNameTracker[i];

            if(qtyStr != "0"){
                QString finalData = itemNameStr+"."+qtyStr+"."+rateStr;
                orders+=finalData;
                orders+=">";
            }

        }
        //Add item to db
        Order_db order_db("database.db");
        order_db.createTable();
        order_db.addItem(userEmail,qDate,orders);

        //End and exit
        this->close();
        users = new Users(this,"straw");
        users->show();
    }
}

void Users::setMyOrdersList(){
    Order_db order_db("database.db");
    //QList<QList<QString>> datas = order_db.getUserOrdersData(this->uemail);
    QList<QList<QString>> datas = order_db.getUserData(this->uemail);

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

        userEmail->setText(data[0]);
        orderDate->setText("Ordered on "+data[1]);
        orderStatus->setText("Order status: "+data[3]);

        QList<QList <QString>> qlist_data = getFromattedList(data[2]);

        QLabel* oder_num = new QLabel();
        oder_num->setText("#" + QString::number(i+1) /*+ " " + data[0]*/);
        hbox->addWidget(oder_num);
//        hbox->addWidget();
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
        hbox->addWidget(br);
        hbox->setMargin(12);

        parentHbox->addItem(hbox);
    }
    //ui->viewOrderList->setLayout(parentHbox);
    ui->scrollAreaWidgetContents->setLayout(parentHbox);
}


QList<QList <QString>> Users::getFromattedList(QString rawData){
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
