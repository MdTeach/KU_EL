#ifndef IDENTITY_H
#define IDENTITY_H
#include<iostream>
#include<string>
using namespace std;

class Customer{
private:
    string Firstname,LastName,email,password,address;
    double phnumber;
public:
    void SetFname(string name){
        this->Firstname = name;
    }
    void SetLname(string name){
        this->LastName = name;
    }
    void Setemail(string email){
        this->email = email;
    }
    void SetPass(string pass){
        this->password = pass;
    }
    void Setaddress(string address){
        this->address = address;
    }

    void setPhone(double num){
        this->phnumber = num;
    }
//    void SetPhone(customer id[],int x){
//        int i;
//        double y;
//        start:{
//        cout<<"enter the phone number:"<<endl;
//        cin>>y;
//          for(i = 0;i<=x;i++){
//            if (y == id[i].phnumber){
//                cout<<"the number is already taken. Please try different phone number"<<endl;
//                goto start;
//                }
//            }
//          }
//        phnumber = y;

//    }

    double getPhnumber(){
        return phnumber;
    }
    string getPass(){
        return password;
    }
};


#endif // IDENTITY_H
