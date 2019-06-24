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

    //ui->welcomeWidget->setCurrentIndex(0);


}

MainWindow::~MainWindow()
{

    delete ui;
}
