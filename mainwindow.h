#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <admindialog.h>
#include <userregister.h>

#include <QtSql>
#include <QDebug>
#include <QFileInfo>


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
//    AdminDialog *adminDialog;
//    UserRegister *userRegister;
};

#endif // MAINWINDOW_H
