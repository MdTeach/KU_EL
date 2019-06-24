#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtSql>
#include <QDebug>
#include <QFileInfo>


#include<home.h>
//#include<admin.h>
//#include<user.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;
    Home *homeStack;
//    User *userStack;
//    Admin *adminStack;
};

#endif // MAINWINDOW_H
