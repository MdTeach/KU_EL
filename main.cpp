#include "mainwindow.h"
#include <QApplication>

static const QString path = "database.db";

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setWindowTitle("KUEL");

    return a.exec();
}
