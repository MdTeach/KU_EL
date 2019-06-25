 #include "users.h"
#include "ui_users.h"

Users::Users(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Users)
{
    ui->setupUi(this);
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
