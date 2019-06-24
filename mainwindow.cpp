#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

#include <QDebug>
#include <db_mannager.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainStack->insertWidget(0,&homeStack);
    ui->mainStack->setCurrentIndex(0);


}

MainWindow::~MainWindow()
{

    delete ui;
}

