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
    QString email = ui->Email->text();
    QString pass1 = ui->Password->text();

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

//    QString fName = ui->Fname->text();
//    QString lName = ui->Lname->text();
//    QString email = ui->Email->text();
//    QString addr = ui->Address->text();
//    QString phn = ui->Number->text();
//    QString pass1 = ui->Password->text();
//    QString pass2 = ui->Password_re->text();

//    if(isEmpty(fName)){
//        QMessageBox :: information (this, "Error!!",  "Firstname field is empty");
//    }else if(isEmpty(lName)){
//        QMessageBox :: information (this, "Error!!", "Lastname field is empty");
//    }else if(isEmpty(email)){
//        QMessageBox :: information (this, "Error!!", "Email field is empty");
//    }else if(isEmpty(addr)){
//        QMessageBox :: information (this, "Error!!", "Address field is empty");
//    }else if(isEmpty(phn)){
//        QMessageBox :: information (this, "Error!!", "Mobile Number field is empty");
//    }else if(isEmpty(pass1)){
//        QMessageBox :: information (this, "Error!!", "Password field is empty");
//    }else if(isEmpty(pass2)){
//        QMessageBox :: information (this, "Error!!", "Reenter Password field is empty");
//    }else{
//        //password confirm
//        if(!(pass1 == pass2)){
//            QMessageBox :: information (this, "Error!!", "Password did't match please try again");
//        }else{
//            QMessageBox :: information (this, "Log In", "Success");
//        }
//    }
    //QString message = fName + lName + email;

}


