QT       += core gui sql charts serialport widgets network printsupport axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console c++17
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    client.cpp \
    githubclient.cpp \
    arduino.cpp \
    connection.cpp \
    projet.cpp \
    formations.cpp \
    formationservice.cpp \
    evaluation.cpp \
    usersession.cpp \
    login.cpp \
    consultants.cpp \
    calendrier.cpp \
    tache.cpp \
    piechartwidget.cpp \
    piechartwidget2.cpp \
    smsservice.cpp \
    ressource.cpp


HEADERS += \
    mainwindow.h \
    client.h \
    githubclient.h \
    arduino.h \
    connection.h \
    projet.h \
    formation.h \
    formationservice.h \
    evaluation.h \
    usersession.h \
    login.h \
    consultants.h \
    calendrier.h \
    tache.h \
    piechartwidget.h \
    piechartwidget2.h \
    smsservice.h \
    ressource.h

FORMS += \
    mainwindow.ui \
    login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
