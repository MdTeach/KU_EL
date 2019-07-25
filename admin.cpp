#include "admin.h"
#include "ui_admin.h"

#include<QDebug>

#include <db_mannager.h>
#include <admin_db.h>
#include <order_db.h>
#include <datetimeformatter.h>
#include <QList>
#include <QDateTime>
#include <QDate>
#include <QTime>

Admin::Admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    //Adding the list of users
    addUserList();

    //Adding items to the list
    addItemList();

    //Adding item to users orders
    addOrderList();

    //Showing analitics
    showAnalitics();


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
            Admin *admin = new Admin(this);
            admin->show();
            ui->stackedWidget->setCurrentIndex(1);
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

void Admin::on_pushButton_2_clicked()
{
    //Show analitics
    ui->stackedWidget->setCurrentIndex(3);
}

void Admin::showAnalitics(){

    //TODO::need to get some order datas that we might already have:
    Order_db order_db("database.db");
    QList<QList<QString>> datas = order_db.getAllData();


    QList<QString> dates;
    for(int i=0;i<datas.length();i++){
        dates.push_front(datas[i][1]);
    }

    DateTimeFormatter df;
    QString qDate = QDate::currentDate().toString();
    QString qTime = QTime::currentTime().toString();
    qDate = qDate + " at " + qTime;

    QList<QList<uint>> formatted_date = df.sortByDate(dates,60*5,qDate);
    qDebug()<<dates;
    qDebug()<<formatted_date;
    qDebug()<<formatted_date.length();

    if(formatted_date[0].length()>0){
        QCustomPlot* customPlot = ui->customPlot;
        customPlot->setBackground(QColor(255, 0, 102).lighter(130));


        // create empty bar chart objects:
        QCPBars *orders = new QCPBars(customPlot->xAxis, customPlot->yAxis);
        orders->setAntialiased(false); // gives more crisp, pixel aligned bar borders

        // set names and colors:
        orders->setName("Orders");
        orders->setPen(QPen(QColor(0, 168, 140).lighter(130)));
        orders->setBrush(QColor(0, 168, 140));
        // stack bars on top of each other:

        // prepare x axis with country labels:
        QVector<double> ticks;
        QVector<double> ordersData;

        QVector<QString> labels;

        uint initalTime = df.getUnixTimeStamp(qDate);
        for(int i = 0 ;i<formatted_date.length();i++){
            ticks.append(i);
            QString that_time = QDateTime::fromTime_t(initalTime).toString();
            labels.append(that_time);
            initalTime+=30;
            ordersData.append(formatted_date[i].length());
        }

        qDebug()<<ordersData;



        QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
        textTicker->addTicks(ticks, labels);
        customPlot->xAxis->setTicker(textTicker);
        customPlot->xAxis->setTickLabelRotation(60);
        customPlot->xAxis->setSubTicks(false);
        customPlot->xAxis->setTickLength(0, 4);
        customPlot->xAxis->setPadding(20);
        customPlot->xAxis->setRange(-1, 8);
        customPlot->xAxis->setBasePen(QPen(Qt::white));
        customPlot->xAxis->setTickPen(QPen(Qt::white));
        customPlot->xAxis->grid()->setVisible(true);
        customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
        customPlot->xAxis->setTickLabelColor(Qt::white);
        customPlot->xAxis->setLabel("Time in last seconds");
        customPlot->xAxis->setLabelColor(Qt::white);

        // prepare y axis:
        customPlot->yAxis->setRange(0, 8);
        customPlot->yAxis->setPadding(20); // a bit more space to the left border
        customPlot->yAxis->setLabel("Orders by the user");
        customPlot->yAxis->setBasePen(QPen(Qt::white));
        customPlot->yAxis->setTickPen(QPen(Qt::white));
        customPlot->yAxis->setSubTickPen(QPen(Qt::white));
        customPlot->yAxis->grid()->setSubGridVisible(true);
        customPlot->yAxis->setTickLabelColor(Qt::white);
        customPlot->yAxis->setLabelColor(Qt::white);
        customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
        customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

        orders->setData(ticks, ordersData);

        // setup legend:
        customPlot->legend->setVisible(true);
        customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
        customPlot->legend->setBrush(QColor(255, 255, 255, 100));
        customPlot->legend->setBorderPen(Qt::NoPen);
        QFont legendFont = font();
        legendFont.setPointSize(10);
        customPlot->legend->setFont(legendFont);
        customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    }else{
        QLabel *qlabel= new QLabel();
        ui->statusText->setText("No orders for the last five minutes");
    }
}
