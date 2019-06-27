#include "users.h"
#include "ui_users.h"

#include<QDebug>
#include<QList>

#include<QHBoxLayout>

#include<db_mannager.h>
#include<admin_db.h>

#include<QSignalMapper>

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

        QHBoxLayout* hbox = new QHBoxLayout();
        QLabel* itemNameLabel = new QLabel();
        QLabel* priceLabel = new QLabel();
        QPushButton* addButton = new QPushButton();
        QPushButton* removeBUtton = new QPushButton();

        // Note: 0->itemName 1->itemCost
        itemNameLabel->setText(itemData[0]);
        priceLabel->setText("Rs "+itemData[1]);

        addButton->setText("+");
        removeBUtton->setText("-");

        QString temp = itemData[0];

        //Addig the function to button
        //QObject::connect(addButton,SIGNAL(clicked()),this,SLOT(sayHi()));


        //Connecting add button
        QSignalMapper* m_sigmapper = new QSignalMapper(this);
        connect(addButton, SIGNAL(clicked()),m_sigmapper, SLOT(map()));
        m_sigmapper->setMapping(addButton,temp);
        connect(m_sigmapper, SIGNAL(mapped(QString)),this, SLOT(addItem(const QString&)));

        //Connecting add button
        QSignalMapper* n_sigmapper = new QSignalMapper(this);
        connect(removeBUtton, SIGNAL(clicked()),n_sigmapper, SLOT(map()));
        n_sigmapper->setMapping(removeBUtton,temp);
        connect(n_sigmapper, SIGNAL(mapped(QString)),this, SLOT(removeItem(const QString&)));

        hbox->addWidget(itemNameLabel);
        hbox->addWidget(priceLabel);
        hbox->addWidget(addButton);
        hbox->addWidget(removeBUtton);

        hbox->setSpacing(50);

        ui->orderItemList->addLayout(hbox);
    }
}

void Users::sayHi(){
    qDebug()<<"was clicked";
}

void Users::addItem(const QString& data){
    qDebug()<<"Add "+data;
}

void Users::removeItem(const QString& data){
    qDebug()<<"Delete "+data;
}
