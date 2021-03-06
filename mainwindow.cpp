#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

#include <QDebug>
#include<QMovie>
#include <db_mannager.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->mainStack->setCurrentIndex(0);

    //Ading the animating gif
    QMovie *movie = new QMovie(":/images/img/clothes.gif");
    ui->welcomeLabel->setMovie(movie);
    movie->start();
}

MainWindow::~MainWindow()
{

    delete ui;
}


//Login Stuff
void MainWindow::on_pushButton_Login_clicked()
{

    QString userName = ui -> lineEdit_userName->text();
    QString password = ui -> lineEdit_password->text();

    DbManager db("database.db");
    bool succ = db.userAuth(userName,password);
    qDebug()<<succ;
    if(userName=="KUEL" && password=="ELforKU54"){
            ui->lineEdit_userName->setText("");
            ui->lineEdit_password->setText("");
            admin = new Admin(this);
            this->hide();
            admin->setFixedSize(870,700);
            admin->show();

    }else if (succ){
        //Login in Sucess
        //Clear the login page
        ui->lineEdit_userName->setText("");
        ui->lineEdit_password->setText("");
        //Show the User window
        hide();

        users = new Users(this, userName);
        users->setFixedSize(870,700);
        users->show();

    }else{
       QMessageBox :: information (this, "Error!!", "Worng username or password");
}
}

void MainWindow::on_homeButton_clicked()
{
    ui->mainStack->setCurrentIndex(0);
}

void MainWindow::on_loginButton_clicked()
{
    ui->mainStack->setCurrentIndex(1);
}

void MainWindow::on_registerButton_clicked()
{
    ui->mainStack->setCurrentIndex(2);
}

void MainWindow::on_aboutButton_clicked()
{
    ui->mainStack->setCurrentIndex(3);
}

void MainWindow::showMessage(MainWindow *context, const QString message){
    QMessageBox :: information (context, "Error!!", message);
}


bool isEmpty(QString string){
    if(string == "" || string == " ") return true;
    return false;
}

void MainWindow::on_adminButton_clicked()
{
    admin = new Admin(this);
    admin->setFixedSize(870,700);
    admin->show();
    this->hide();
}

void MainWindow::on_userButton_clicked()
{
    users = new Users(this,"straw");
    users->setFixedSize(870,700);
    users->show();
    this->hide();
}

void MainWindow::on_registerButton_2_clicked()
{
    //Getting objs from the ui
    QString email = ui->Email->text();
    QString pass1 = ui->Password->text();

    QString fName = ui->Fname->text();
    QString lName = ui->Lname->text();
    //QString email = ui->Email->text();
    QString addr = ui->Address->text();
    QString phn = ui->Number->text();
    //QString pass1 = ui->Password->text();
    QString pass2 = ui->Password_re->text();


    QRegExp re("^[0-9]{10}$");

    // DataValidation
    if(isEmpty(fName)){
        this->showMessage(this, "Firstname field is empty");
    }else if(isEmpty(lName)){
        this->showMessage(this, "Lastname field is empty");
    }else if(isEmpty(email)){
        this->showMessage(this, "Email field is empty");
    }else if(isEmpty(addr)){
        this->showMessage(this, "Address field is empty");
    }else if(!(re.exactMatch(phn))){
        this->showMessage(this, "Phone not entered correctly.");
    }else if(isEmpty(pass1)){
        this->showMessage(this, "Password 1 field is empty");
    }else if(isEmpty(pass2)){
        this->showMessage(this, "Password 2 field is empty");
    }else{
        //password confirm
        if(!(pass1 == pass2)){
            this->showMessage(this, "Password didn't match");
        }else{
            //add user data to the database
            DbManager db("database.db");
            if(!db.isOpen()){
                qDebug()<<"Database not opening";
            }else{
                db.createTable();   // Creates a table if it doens't exist. Otherwise, it will use existing table.
                if(db.emailExists(email)){
                    //email already taken :(
                    QMessageBox :: information (this, "Error!!", "Email is already taken. Try another one");
                }else{
                    qDebug()<<"Adding"<<email<<pass1;
                    if(db.addUser(email,pass1,fName,lName,addr,phn)){
                        qDebug()<<"Sucess";
                        QMessageBox::information(this,"Success", "Registered Sucessfully");
                        ui->Email->setText("");
                        ui->Password->setText("");
                        ui->Fname->setText("");
                        ui->Lname->setText("");
                        ui->Address->setText("");
                        ui->Number->setText("");
                        ui->Password_re->setText("");
                        ui->lineEdit_userName->setText(email);
                        ui->mainStack->setCurrentIndex(1);
                    }else{
                        qDebug()<<"Failed";
                    }
                }
            }
        }
    }

}
