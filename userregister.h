#ifndef USERREGISTER_H
#define USERREGISTER_H

#include <QDialog>

namespace Ui {
class UserRegister;
}

class UserRegister : public QDialog
{
    Q_OBJECT

public:
    explicit UserRegister(QWidget *parent = nullptr);
    ~UserRegister();
   void showMessage(UserRegister* context, const QString message);

private slots:
    void on_pushButton_clicked();

private:
    Ui::UserRegister *ui;
};

#endif // USERREGISTER_H
