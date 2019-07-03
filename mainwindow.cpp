#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

#include <QDebug>
#include<QMovie>
#include <db_mannager.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->mainStack->setCurrentIndex(0);

    //Ading the animating gif
    QMovie *movie = new QMovie(":/images/img/clothes.gif");
    ui->gifLabel->setMovie(movie);
    movie->start();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_homeButton_clicked() {
    ui->mainStack->setCurrentIndex(0);
}

void MainWindow::on_loginButton_clicked() {
    ui->mainStack->setCurrentIndex(1);
}

void MainWindow::on_registerButton_clicked() {
    ui->mainStack->setCurrentIndex(2);
}

void MainWindow::on_aboutButton_clicked() {
    ui->mainStack->setCurrentIndex(3);
}


//Login Stuff
void MainWindow::on_pushButton_login_clicked() {
    QString email = ui -> lineEdit_email->text();
    QString password = ui -> lineEdit_password->text();

    DbManager db("database.db");
    bool succ = db.userAuth(email, password);
    qDebug()<<succ;
    if(!succ) {
        //login failed show error message
        QMessageBox :: information (this, "Error!!", "Worng email or password");
    } else {
        //Login in Sucess
        //Clear the login page
        ui->lineEdit_email->setText("");
        ui->lineEdit_password->setText("");
        //Show the User window
        hide();

        users = new Users(this, email);
        users->show();
    }
}

void MainWindow::showMessage(MainWindow *context, const QString message) {
    QMessageBox :: information (context, "Error!!", message);
}

bool isEmpty(QString string){
    if(string == "" || string == " ") return true;
    return false;
}

void MainWindow::on_adminButton_clicked()
{
    admin = new Admin(this);
    admin->show();
    this->hide();
}

void MainWindow::on_userButton_clicked()
{
    users = new Users(this,"straw");
    users->show();
    this->hide();
}

void MainWindow::on_pushButton_register_clicked() {
    //Getting objs from the ui
    QString email = ui->Email->text();
    QString pass1 = ui->Password->text();

    QString fname = ui->Fname->text();
    QString lname = ui->Lname->text();
    //QString email = ui->Email->text();
    QString addr = ui->Address->text();
    QString phn = ui->Number->text();
    //QString pass1 = ui->Password->text();
    QString pass2 = ui->Password_re->text();

    //DataValidation
    if(isEmpty(fname)) {
        this->showMessage(this, "Firstname field is empty");
    } else if(isEmpty(lname)) {
        this->showMessage(this, "Lastname field is empty");
    } else if(isEmpty(email)) {
        this->showMessage(this, "Email field is empty");
    } else if(isEmpty(addr)) {
        this->showMessage(this, "Address field is empty");
    } else if(isEmpty(phn)) {
        this->showMessage(this, "Phone field is empty");
    } else if(isEmpty(pass1)) {
        this->showMessage(this, "Password 1 field is empty");
    } else if(isEmpty(pass2)) {
        this->showMessage(this, "Password 2 field is empty");
    } else {
        //password confirm
        if(!(pass1 == pass2)) {
            this->showMessage(this, "Password didn't match");
        } else {
            //add user data to the database
            DbManager db("database.db");
            if(db.isOpen()) {
                db.createTable();   // Creates a table if it doens't exist. Otherwise, it will use existing table.
                if(db.emailExists(email)){
                    //email already taken :(
                    QMessageBox :: information (this, "Error!!", "Email is already taken try another one");
                } else {
                    qDebug()<<"Adding"<<email<<pass1;
                    if(db.addUser(fname, lname, email, pass1, addr, phn)) {
                        qDebug()<<"Sucess";
                        QMessageBox::information(this,"Success", "Registered Sucessfully");
                        ui->mainStack->setCurrentIndex(1);
                    } else {
                        qDebug()<<"Failed";
                    }
                }
            }
        }
    }
}
