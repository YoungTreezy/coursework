QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cashbox.cpp \
    cashier.cpp \
    main.cpp \
    main_menu.cpp \
    mainwindow.cpp \
    product.cpp \
    receipt.cpp \
    requests.cpp

HEADERS += \
    cashbox.h \
    cashier.h \
    main_menu.h \
    mainwindow.h \
    product.h \
    receipt.h \
    requests.h

FORMS += \
    cashbox.ui \
    cashier.ui \
    main_menu.ui \
    mainwindow.ui \
    product.ui \
    receipt.ui \
    requests.ui

TRANSLATIONS += \
    coursework_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
