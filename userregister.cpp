#include "userregister.h"
#include "ui_userregister.h"
#include "qmessagebox.h"
#include "QDebug"
#include "db_mannager.h"

UserRegister::UserRegister(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserRegister)
{
    ui->setupUi(this);
}

UserRegister::~UserRegister()
{
    delete ui;
}

bool isEmpty(QString string){
    if(string == "" || string == " ") return true;
    return false;
}


void UserRegister::on_pushButton_clicked()
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

    //DataValidation
    if(isEmpty(fName)){
        this->showMessage(this, "Firstname field is empty");
    }else if(isEmpty(lName)){
        this->showMessage(this, "Lastname field is empty");
    }else if(isEmpty(email)){
        this->showMessage(this, "Email field is empty");
    }else if(isEmpty(addr)){
        this->showMessage(this, "Address field is empty");
    }else if(isEmpty(phn)){
        this->showMessage(this, "Phone field is empty");
    }else if(isEmpty(pass1)){
        this->showMessage(this, "Password 1 field is empty");
    }else if(isEmpty(pass2)){
        this->showMessage(this, "Password 2 field is empty");
    }else{
        //password confirm
        if(!(pass1 == pass2)){
            this->showMessage(this, "Password didn't match");
        }else{
            QMessageBox :: information (this, "Suceess!!", "Registered!");
        }
    }
    //QString message = fName + lName + email;

    //add user name to the database
    DbManager db("database.db");
    if(!db.isOpen()){
        qDebug()<<"Database not opening";
    }else{
        db.createTable();   // Creates a table if it doens't exist. Otherwise, it will use existing table.
        if(db.emailExists(email)){
            //email already taken :(
            QMessageBox :: information (this, "Error!!", "Email is already taken try another one");
        }else{
            qDebug()<<"Adding"<<email<<pass1;
            (db.addUser(email,pass1)) ? qDebug()<<"Sucess" :qDebug()<<"Failed";
        }

    }

}

void UserRegister::showMessage(UserRegister* context, const QString message){
    QMessageBox :: information (context, "Error!!", message);
}


