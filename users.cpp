#include "users.h"
#include "ui_users.h"

#include<QDebug>
#include<QList>

#include<QHBoxLayout>

#include<db_mannager.h>
#include<admin_db.h>
#include<order_db.h>

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
    qDebug()<<"Add Data";
    if(ui->grandTotalLabel->text() ==  "0"){
        //0 items added show error
        qDebug()<<"Please select some items";
    }else{
        qDebug()<<"Adding to db..";
        //Preparing data
        QString userEmail = this->uemail;
        QString qDate = "today";
        QString orders;

        for(int i=0; i<this->qtyTracker.length();i++){
            QLabel* rate = costTracker[i];
            QSpinBox* spinBox = qtyTracker[i];

            QString rateStr = rate->text();
            QString qtyStr = spinBox->text();
            QString itemNameStr = itemNameTracker[i];

            orders+="<";
            QString finalData = itemNameStr+"."+qtyStr+"."+rateStr;
            orders+=">";
        }

        //Add item to db
        Order_db order_db("database.db");
        order_db.createTable();
        order_db.addItem(userEmail,qDate,orders);

    }
}
