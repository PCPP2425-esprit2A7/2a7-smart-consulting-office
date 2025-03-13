/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QGroupBox *groupBox_7;
    QLabel *label_33;
    QLabel *label_34;
    QLabel *label_35;
    QLineEdit *description;
    QLineEdit *priorite;
    QLabel *label_36;
    QLineEdit *nom;
    QLabel *label_37;
    QLineEdit *statut;
    QPushButton *ajoute;
    QPushButton *modifier;
    QDateEdit *datee;
    QGroupBox *groupBox_6;
    QTableView *aff;
    QPushButton *sup;
    QPushButton *recuperer;
    QLineEdit *idedit;
    QLabel *label_3;
    QLabel *label_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1069, 623);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(-70, -80, 1131, 771));
        label->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/abstract-paper-background-concept.jpg);"));
        groupBox_7 = new QGroupBox(centralwidget);
        groupBox_7->setObjectName("groupBox_7");
        groupBox_7->setGeometry(QRect(40, 30, 301, 511));
        groupBox_7->setMinimumSize(QSize(301, 511));
        groupBox_7->setStyleSheet(QString::fromUtf8("QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;  /* Center the title */\n"
"    padding: 0 10px;\n"
"    background-color: rgba(0,0,0,0,);  /* Yellow background for the title */\n"
"    color: rgb(255, 255, 255)ck;\n"
"    font-weight: bold;\n"
"    border-radius: 4px;\n"
"}\n"
"QGroupBox {\n"
"    background-color: transparent;  /* Transparent to blend with the rest of the interface */\n"
"    border: 2px solid rgba(0,0,0,0,);  /* Yellow border to match the rest */\n"
"    border-radius: 8px;\n"
"    margin-top: 10px;\n"
"    padding: 10px;\n"
"}\n"
"QLineEdit {\n"
"    background-color: transparent;  /* Make the input fields transparent */\n"
"    border: 2px solid rgba(248, 248, 147, 255);  /* Yellow border to maintain consistency */\n"
"    border-radius: 8px;  /* Rounded corners for a smooth look */\n"
"    padding: 5px;  /* Padding to give space inside the input */\n"
"    color: white;  /* Text color to ensure visibility */\n"
"    font-size: 14px;  /* Adju"
                        "st font size */\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 2px solid rgba(255, 255, 147, 255);  /* Brighter border when the input is focused */\n"
"    background-color: rgba(255, 255, 255, 0.2);  /* Light translucent background on focus */\n"
"}\n"
"QLabel {\n"
"    color: black;  /* Text color to match the interface */\n"
"    background-color: transparent;  /* Transparent background */\n"
"    font-weight: bold;  /* Bold text to make the labels stand out */\n"
"    font-size: 14px;  /* Adjust the font size */\n"
"    padding: 5px;  /* Add some space around the label */\n"
"}\n"
"\n"
"QLabel:hover {\n"
"    color: rgba(248, 248, 147, 255);  /* Yellow text on hover */\n"
"}\n"
""));
        label_33 = new QLabel(groupBox_7);
        label_33->setObjectName("label_33");
        label_33->setGeometry(QRect(0, 120, 131, 31));
        label_34 = new QLabel(groupBox_7);
        label_34->setObjectName("label_34");
        label_34->setGeometry(QRect(0, 180, 121, 31));
        label_35 = new QLabel(groupBox_7);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(0, 250, 131, 21));
        description = new QLineEdit(groupBox_7);
        description->setObjectName("description");
        description->setGeometry(QRect(140, 180, 151, 31));
        priorite = new QLineEdit(groupBox_7);
        priorite->setObjectName("priorite");
        priorite->setGeometry(QRect(140, 300, 151, 31));
        label_36 = new QLabel(groupBox_7);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(0, 310, 131, 21));
        nom = new QLineEdit(groupBox_7);
        nom->setObjectName("nom");
        nom->setGeometry(QRect(140, 120, 151, 31));
        label_37 = new QLabel(groupBox_7);
        label_37->setObjectName("label_37");
        label_37->setGeometry(QRect(0, 370, 141, 21));
        statut = new QLineEdit(groupBox_7);
        statut->setObjectName("statut");
        statut->setGeometry(QRect(140, 360, 151, 31));
        ajoute = new QPushButton(groupBox_7);
        ajoute->setObjectName("ajoute");
        ajoute->setGeometry(QRect(20, 440, 111, 41));
        ajoute->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: none;\n"
"    background-color: qlineargradient(\n"
"        spread:pad, x1:0, y1:0, x2:1, y2:1, \n"
"        stop:0 #2b2b2b,   /* Noir fonc\303\251 */\n"
"        stop:0.5 #1e1e1e, /* Noir interm\303\251diaire */\n"
"        stop:1 #000000    /* Noir profond */\n"
"    );\n"
"    color: white;              /* Texte en blanc */\n"
"    border: 2px solid #555;    /* Bordure gris fonc\303\251 */\n"
"    border-radius: 10px;       /* Coins arrondis */\n"
"    padding: 10px 20px;        /* Espacement interne */\n"
"    font-size: 14px;           /* Taille du texte */\n"
"    font-weight: bold;         /* Texte en gras */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: none;\n"
"    background-color: qlineargradient(\n"
"        spread:pad, x1:0, y1:0, x2:1, y2:1,\n"
"        stop:0 #3b3b3b,  /* Gris plus clair au survol */\n"
"        stop:0.5 #292929,  \n"
"        stop:1 #121212  \n"
"    );\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background: none;\n"
"    background"
                        "-color: #1a1a1a;  /* Noir encore plus profond lors de l'appui */\n"
"}\n"
"\n"
"QPushButton:focus {\n"
"    outline: none; /* Supprime l'effet de focus (contour) */\n"
"}\n"
""));
        modifier = new QPushButton(groupBox_7);
        modifier->setObjectName("modifier");
        modifier->setGeometry(QRect(150, 440, 131, 41));
        modifier->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: qlineargradient(\n"
"        spread:pad, x1:0, y1:0, x2:1, y2:1, \n"
"        stop:0 #2b2b2b,   /* Noir fonc\303\251 */\n"
"        stop:0.5 #1e1e1e, /* Noir interm\303\251diaire */\n"
"        stop:1 #000000    /* Noir profond */\n"
"    );\n"
"    color: white;              /* Texte en blanc */\n"
"    border: 2px solid #555;    /* Bordure gris fonc\303\251 */\n"
"    border-radius: 10px;       /* Coins arrondis */\n"
"    padding: 10px 20px;        /* Espacement interne */\n"
"    font-size: 14px;           /* Taille du texte */\n"
"    font-weight: bold;         /* Texte en gras */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: qlineargradient(\n"
"        spread:pad, x1:0, y1:0, x2:1, y2:1,\n"
"        stop:0 #3b3b3b,  /* Gris plus clair au survol */\n"
"        stop:0.5 #292929,  \n"
"        stop:1 #121212  \n"
"    );\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #1a1a1a;  /* Noir encore plus profond lors de l'appui */\n"
"}\n"
""));
        datee = new QDateEdit(groupBox_7);
        datee->setObjectName("datee");
        datee->setGeometry(QRect(150, 250, 141, 22));
        groupBox_6 = new QGroupBox(centralwidget);
        groupBox_6->setObjectName("groupBox_6");
        groupBox_6->setGeometry(QRect(590, 150, 451, 421));
        groupBox_6->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color:white;\n"
"    border: 2px solid rgba(0,0,0,0);  /* Same yellow border */\n"
"    border-radius: 8px;\n"
"    gridline-color: rgba(0,0,0,0);  /* Match gridline with the border color */\n"
"    font-size: 14px;\n"
"    color: #333;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    padding: 5px;\n"
"    border: none;\n"
"    background-color: rgba(0,0,0,0);  /* Light transparent yellow for rows */\n"
"    color: #000;\n"
"}\n"
"\n"
"QTableWidget::item:selected {\n"
"    background-color: rgba(0,0,0,0);  /* Highlight with a more opaque yellow */\n"
"    color:white;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: rgba(0,0,0,0);  /* Yellow header */\n"
"    color: black;\n"
"    font-weight: bold;\n"
"    padding: 5px;\n"
"    border: 1px solid rgba(255,255,255,255);\n"
"}\n"
"\n"
"QScrollBar:vertical {\n"
"    border: none;\n"
"    background-color: white;\n"
"    width: 10px;\n"
"    margin: 0px 0px 0px 0px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    ba"
                        "ckground-color: rgba(0,0,0,0);  /* Yellow scrollbar */\n"
"    min-height: 30px;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical,\n"
"QScrollBar::sub-line:vertical {\n"
"    border: none;\n"
"    background: none;\n"
"}\n"
"QGroupBox {\n"
"    background-color: transparent;  /* Transparent to blend with the rest of the interface */\n"
"    border: 2px solid rgba(0,0,0,0);  /* Yellow border to match the rest */\n"
"    border-radius: 8px;\n"
"    margin-top: 10px;\n"
"    padding: 10px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;  /* Center the title */\n"
"    padding: 0 10px;\n"
"    background-color: rgba(0,0,0,0);  /* Yellow background for the title */\n"
"    color:black;\n"
"    font-weight: bold;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
""));
        aff = new QTableView(groupBox_6);
        aff->setObjectName("aff");
        aff->setGeometry(QRect(40, 20, 451, 341));
        sup = new QPushButton(groupBox_6);
        sup->setObjectName("sup");
        sup->setGeometry(QRect(40, 370, 131, 41));
        sup->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: qlineargradient(\n"
"        spread:pad, x1:0, y1:0, x2:1, y2:1, \n"
"        stop:0 #2b2b2b,   /* Noir fonc\303\251 */\n"
"        stop:0.5 #1e1e1e, /* Noir interm\303\251diaire */\n"
"        stop:1 #000000    /* Noir profond */\n"
"    );\n"
"    color: white;              /* Texte en blanc */\n"
"    border: 2px solid #555;    /* Bordure gris fonc\303\251 */\n"
"    border-radius: 10px;       /* Coins arrondis */\n"
"    padding: 10px 20px;        /* Espacement interne */\n"
"    font-size: 14px;           /* Taille du texte */\n"
"    font-weight: bold;         /* Texte en gras */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: qlineargradient(\n"
"        spread:pad, x1:0, y1:0, x2:1, y2:1,\n"
"        stop:0 #3b3b3b,  /* Gris plus clair au survol */\n"
"        stop:0.5 #292929,  \n"
"        stop:1 #121212  \n"
"    );\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #1a1a1a;  /* Noir encore plus profond lors de l'appui */\n"
"}\n"
""));
        recuperer = new QPushButton(groupBox_6);
        recuperer->setObjectName("recuperer");
        recuperer->setGeometry(QRect(190, 370, 111, 41));
        recuperer->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: qlineargradient(\n"
"        spread:pad, x1:0, y1:0, x2:1, y2:1, \n"
"        stop:0 #2b2b2b,   /* Noir fonc\303\251 */\n"
"        stop:0.5 #1e1e1e, /* Noir interm\303\251diaire */\n"
"        stop:1 #000000    /* Noir profond */\n"
"    );\n"
"    color: white;              /* Texte en blanc */\n"
"    border: 2px solid #555;    /* Bordure gris fonc\303\251 */\n"
"    border-radius: 10px;       /* Coins arrondis */\n"
"    padding: 10px 20px;        /* Espacement interne */\n"
"    font-size: 14px;           /* Taille du texte */\n"
"    font-weight: bold;         /* Texte en gras */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: qlineargradient(\n"
"        spread:pad, x1:0, y1:0, x2:1, y2:1,\n"
"        stop:0 #3b3b3b,  /* Gris plus clair au survol */\n"
"        stop:0.5 #292929,  \n"
"        stop:1 #121212  \n"
"    );\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #1a1a1a;  /* Noir encore plus profond lors de l'appui */\n"
"}\n"
""));
        idedit = new QLineEdit(groupBox_6);
        idedit->setObjectName("idedit");
        idedit->setGeometry(QRect(312, 371, 131, 31));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(350, 0, 191, 231));
        label_3->setStyleSheet(QString::fromUtf8("\n"
"image: url(:/new/prefix3/result.png);"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(950, 10, 101, 71));
        label_2->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix5/ttqqq-removebg-preview.png);\n"
"image: url(:/new/prefix5/ttqqq-removebg-preview.png);"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1069, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QString());
        groupBox_7->setTitle(QCoreApplication::translate("MainWindow", "ajouter un tache", nullptr));
        label_33->setText(QCoreApplication::translate("MainWindow", "NOM", nullptr));
        label_34->setText(QCoreApplication::translate("MainWindow", "DESCRIPTION", nullptr));
        label_35->setText(QCoreApplication::translate("MainWindow", "DATEE", nullptr));
        label_36->setText(QCoreApplication::translate("MainWindow", "PRIORITE", nullptr));
        label_37->setText(QCoreApplication::translate("MainWindow", "STATUT", nullptr));
        ajoute->setText(QCoreApplication::translate("MainWindow", "ajouter", nullptr));
        modifier->setText(QCoreApplication::translate("MainWindow", "modifier", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "liste des taches", nullptr));
        sup->setText(QCoreApplication::translate("MainWindow", "supprimer", nullptr));
        recuperer->setText(QCoreApplication::translate("MainWindow", "afficher", nullptr));
        label_3->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
