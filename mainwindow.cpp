#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "identity.h"

#include <QDebug>
#include <db_mannager.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);



}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
        ui->mainStack->addWidget(homeStack);
        ui->mainStack->addWidget(userStack);
        ui->mainStack->addWidget(adminStack);

}
