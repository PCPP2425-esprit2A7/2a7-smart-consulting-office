<<<<<<< HEAD
QT       += core gui sql charts serialport widgets network printsupport axcontainer
=======
<<<<<<< HEAD
QT       += core gui sql charts serialport widgets network
=======
QT       += core gui sql charts serialport widgets network printsupport axcontainer
>>>>>>> 00ca2d6ddb272cb69d6813b4c25604876d18434f
>>>>>>> 64944a0beb23206c62f4e06e257680e77b7f15af

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
<<<<<<< HEAD
=======
<<<<<<< HEAD
    projet.cpp
=======
>>>>>>> 64944a0beb23206c62f4e06e257680e77b7f15af
    projet.cpp \
    formations.cpp \
    formationservice.cpp \
    evaluation.cpp \
    usersession.cpp \
    login.cpp \
<<<<<<< HEAD
    consultants.cpp
=======
    consultants.cpp \
    calendrier.cpp \
    tache.cpp \
    piechartwidget.cpp
>>>>>>> 00ca2d6ddb272cb69d6813b4c25604876d18434f
>>>>>>> 64944a0beb23206c62f4e06e257680e77b7f15af

HEADERS += \
    mainwindow.h \
    client.h \
    githubclient.h \
    arduino.h \
    connection.h \
<<<<<<< HEAD
=======
<<<<<<< HEAD
    projet.h

FORMS += \
    mainwindow.ui
=======
>>>>>>> 64944a0beb23206c62f4e06e257680e77b7f15af
    projet.h \
    formation.h \
    formationservice.h \
    evaluation.h \
    usersession.h \
    login.h \
<<<<<<< HEAD
    consultants.h
=======
    consultants.h \
    calendrier.h \
    tache.h \
    piechartwidget.h
>>>>>>> 64944a0beb23206c62f4e06e257680e77b7f15af

FORMS += \
    mainwindow.ui \
    login.ui
<<<<<<< HEAD
=======
>>>>>>> 00ca2d6ddb272cb69d6813b4c25604876d18434f
>>>>>>> 64944a0beb23206c62f4e06e257680e77b7f15af

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
<<<<<<< HEAD

RESOURCES += \
    Resources.qrc
=======
<<<<<<< HEAD
=======

RESOURCES += \
    Resources.qrc
>>>>>>> 00ca2d6ddb272cb69d6813b4c25604876d18434f
>>>>>>> 64944a0beb23206c62f4e06e257680e77b7f15af
