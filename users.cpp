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
