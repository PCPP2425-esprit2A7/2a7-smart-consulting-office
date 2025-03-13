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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QGroupBox *groupBox_7;
    QLabel *nom_;
    QLabel *fournisseur_;
    QLabel *cout_;
    QLineEdit *fournisseur;
    QLineEdit *cout;
    QLineEdit *quantite;
    QLabel *quantite_;
    QLineEdit *nom;
    QLabel *etat_;
    QLineEdit *etat;
    QPushButton *ajoute;
    QPushButton *recuperer;
    QLabel *tel_fournisseur_;
    QLineEdit *tel_fournisseur;
    QGroupBox *groupBox_6;
    QTableView *aff;
    QPushButton *sup;
    QPushButton *modifier;
    QLineEdit *idedit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1179, 701);
        MainWindow->setStyleSheet(QString::fromUtf8("\n"
"image: url(:/new/prefix1/3312919.jpg);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(360, 390, 281, 181));
        label->setPixmap(QPixmap(QString::fromUtf8("6922145.jpg")));
        label->setScaledContents(true);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(-160, -160, 1461, 861));
        label_2->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix3/abstract-paper-background-concept.jpg);"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(860, 20, 261, 201));
        label_3->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/image-removebg-preview.png);"));
        groupBox_7 = new QGroupBox(centralwidget);
        groupBox_7->setObjectName("groupBox_7");
        groupBox_7->setGeometry(QRect(30, 170, 311, 521));
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
        nom_ = new QLabel(groupBox_7);
        nom_->setObjectName("nom_");
        nom_->setGeometry(QRect(10, 130, 131, 31));
        fournisseur_ = new QLabel(groupBox_7);
        fournisseur_->setObjectName("fournisseur_");
        fournisseur_->setGeometry(QRect(10, 190, 121, 31));
        cout_ = new QLabel(groupBox_7);
        cout_->setObjectName("cout_");
        cout_->setGeometry(QRect(10, 250, 131, 21));
        fournisseur = new QLineEdit(groupBox_7);
        fournisseur->setObjectName("fournisseur");
        fournisseur->setGeometry(QRect(140, 190, 151, 31));
        cout = new QLineEdit(groupBox_7);
        cout->setObjectName("cout");
        cout->setGeometry(QRect(140, 240, 151, 31));
        quantite = new QLineEdit(groupBox_7);
        quantite->setObjectName("quantite");
        quantite->setGeometry(QRect(140, 300, 151, 31));
        quantite_ = new QLabel(groupBox_7);
        quantite_->setObjectName("quantite_");
        quantite_->setGeometry(QRect(0, 310, 131, 21));
        nom = new QLineEdit(groupBox_7);
        nom->setObjectName("nom");
        nom->setGeometry(QRect(140, 130, 151, 31));
        etat_ = new QLabel(groupBox_7);
        etat_->setObjectName("etat_");
        etat_->setGeometry(QRect(0, 370, 141, 21));
        etat = new QLineEdit(groupBox_7);
        etat->setObjectName("etat");
        etat->setGeometry(QRect(140, 360, 151, 31));
        ajoute = new QPushButton(groupBox_7);
        ajoute->setObjectName("ajoute");
        ajoute->setGeometry(QRect(20, 460, 111, 41));
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
        recuperer = new QPushButton(groupBox_7);
        recuperer->setObjectName("recuperer");
        recuperer->setGeometry(QRect(160, 460, 111, 41));
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
        tel_fournisseur_ = new QLabel(groupBox_7);
        tel_fournisseur_->setObjectName("tel_fournisseur_");
        tel_fournisseur_->setGeometry(QRect(0, 420, 141, 21));
        tel_fournisseur = new QLineEdit(groupBox_7);
        tel_fournisseur->setObjectName("tel_fournisseur");
        tel_fournisseur->setGeometry(QRect(140, 420, 151, 31));
        groupBox_6 = new QGroupBox(centralwidget);
        groupBox_6->setObjectName("groupBox_6");
        groupBox_6->setGeometry(QRect(500, 250, 651, 421));
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
        aff->setGeometry(QRect(10, 20, 631, 341));
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
        modifier = new QPushButton(groupBox_6);
        modifier->setObjectName("modifier");
        modifier->setGeometry(QRect(220, 370, 111, 41));
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
        idedit = new QLineEdit(groupBox_6);
        idedit->setObjectName("idedit");
        idedit->setGeometry(QRect(412, 370, 151, 41));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        groupBox_7->setTitle(QCoreApplication::translate("MainWindow", "ajouter ressource", nullptr));
        nom_->setText(QCoreApplication::translate("MainWindow", "nom", nullptr));
        fournisseur_->setText(QCoreApplication::translate("MainWindow", "fournisseur", nullptr));
        cout_->setText(QCoreApplication::translate("MainWindow", "cout", nullptr));
        quantite_->setText(QCoreApplication::translate("MainWindow", "quantite", nullptr));
        etat_->setText(QCoreApplication::translate("MainWindow", "etat", nullptr));
        ajoute->setText(QCoreApplication::translate("MainWindow", "ajouter", nullptr));
        recuperer->setText(QCoreApplication::translate("MainWindow", "afficher", nullptr));
        tel_fournisseur_->setText(QCoreApplication::translate("MainWindow", "tel_fournisseur", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "liste des ressources", nullptr));
        sup->setText(QCoreApplication::translate("MainWindow", "supprimer", nullptr));
        modifier->setText(QCoreApplication::translate("MainWindow", "modifier", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
