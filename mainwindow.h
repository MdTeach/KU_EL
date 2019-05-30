#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <admindialog.h>
#include <userregister.h>

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
    void on_pushButton_Login_clicked();

    void on_pushButton_Login_2_clicked();

private:
    Ui::MainWindow *ui;
    AdminDialog *adminDialog;
    UserRegister *userRegister;
};

#endif // MAINWINDOW_H
