#-------------------------------------------------
#
# Project created by QtCreator 2019-05-15T07:56:50
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        admin.cpp \
        admin_db.cpp \
        db_mannager.cpp \
        main.cpp \
        mainwindow.cpp \
        order_db.cpp \
        users.cpp

HEADERS += \
        admin.h \
        admin_db.h \
        db_mannager.h \
        mainwindow.h \
        order_db.h \
        users.h

FORMS += \
        admin.ui \
        mainwindow.ui \
        users.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    ../../KU_EL/po.jpg \
    po.jpg
