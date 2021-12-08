QT       += core gui
QT += widgets
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    creditswindow.cpp \
    main.cpp \
    mainwindow.cpp \
    oknogry.cpp \
    oknowyborugraczy.cpp \
    plansza.cpp \
    wyswietlaniegraczy.cpp

HEADERS += \
    creditswindow.h \
    mainwindow.h \
    oknogry.h \
    oknowyborugraczy.h \
    plansza.h \
    wyswietlaniegraczy.h

FORMS += \
    creditswindow.ui \
    mainwindow.ui \
    oknogry.ui \
    oknowyborugraczy.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc
