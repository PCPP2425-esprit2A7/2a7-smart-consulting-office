/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QWidget *widget;
    QFrame *frame;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_nom;
    QLineEdit *lineEdit_nom_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_7;
    QLabel *label_9;
    QLabel *label_10;
    QWidget *page_2;
    QLabel *label_3;
    QLabel *label_4;
    QComboBox *rolebox_3;
    QLabel *course_ending_7;
    QLabel *course_ending_6;
    QLineEdit *lineEdit_password_3;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QLineEdit *lineEdit_password_5;
    QLabel *course_ending_9;
    QWidget *page_3;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *course_ending_8;
    QLineEdit *lineEdit_password_4;
    QPushButton *pushButton_4;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(1600, 900);
        widget = new QWidget(Login);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 1611, 911));
        frame = new QFrame(widget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(-1, -1, 1611, 911));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        stackedWidget = new QStackedWidget(frame);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(-1, -1, 1601, 901));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        label = new QLabel(page);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 1611, 901));
        label->setPixmap(QPixmap(QString::fromUtf8("../../Pictures/6706379_3418448 (4).jpg")));
        label->setScaledContents(true);
        label_2 = new QLabel(page);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(380, 140, 971, 721));
        label_2->setStyleSheet(QStringLiteral(""));
        label_2->setPixmap(QPixmap(QString::fromUtf8("../_Pngtree_flat_login_user_interface_3726150-removebg.png")));
        lineEdit_nom = new QLineEdit(page);
        lineEdit_nom->setObjectName(QStringLiteral("lineEdit_nom"));
        lineEdit_nom->setGeometry(QRect(660, 370, 411, 61));
        lineEdit_nom->setStyleSheet(QLatin1String("color: black;\n"
"font-family: Arial; /* Change \"Arial\" to your desired font family */\n"
"font-size: 34px; /* Change \"14px\" to your desired font size */"));
        lineEdit_nom_2 = new QLineEdit(page);
        lineEdit_nom_2->setObjectName(QStringLiteral("lineEdit_nom_2"));
        lineEdit_nom_2->setGeometry(QRect(660, 440, 411, 61));
        lineEdit_nom_2->setStyleSheet(QLatin1String("color: black;\n"
"font-family: Arial; /* Change \"Arial\" to your desired font family */\n"
"font-size: 34px; /* Change \"14px\" to your desired font size */"));
        pushButton = new QPushButton(page);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(720, 570, 291, 61));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        pushButton->setFont(font);
        pushButton->setStyleSheet(QLatin1String("color: rgb(85, 170, 255);\n"
""));
        pushButton_2 = new QPushButton(page);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(660, 510, 241, 31));
        pushButton_2->setFont(font);
        label_7 = new QLabel(page);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(700, 310, 311, 41));
        label_7->setStyleSheet(QLatin1String("color: white;\n"
"color: rgb(85, 170, 255);\n"
"font-family: Arial; /* Change \"Arial\" to your desired font family */\n"
"font-size: 34px; /* Change \"14px\" to your desired font size */"));
        label_9 = new QLabel(page);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(560, 380, 91, 41));
        label_9->setStyleSheet(QLatin1String("\n"
"font-family: Arial; /* Change \"Arial\" to your desired font family */\n"
"font-size: 12px; /* Change \"14px\" to your desired font size */"));
        label_10 = new QLabel(page);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(510, 450, 171, 41));
        label_10->setStyleSheet(QLatin1String("\n"
"font-family: Arial; /* Change \"Arial\" to your desired font family */\n"
"font-size: 12px; /* Change \"14px\" to your desired font size */"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        label_3 = new QLabel(page_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 0, 1611, 901));
        label_3->setPixmap(QPixmap(QString::fromUtf8("../../Pictures/6706379_3418448 (4).jpg")));
        label_3->setScaledContents(true);
        label_4 = new QLabel(page_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(350, 160, 911, 611));
        label_4->setPixmap(QPixmap(QString::fromUtf8("../17893271_5931274-removebg-preview (1).png")));
        rolebox_3 = new QComboBox(page_2);
        rolebox_3->setObjectName(QStringLiteral("rolebox_3"));
        rolebox_3->setGeometry(QRect(550, 380, 521, 51));
        rolebox_3->setStyleSheet(QLatin1String("color: black;\n"
"font-family: Arial; /* Change \"Arial\" to your desired font family */\n"
"font-size: 16px; /* Change \"14px\" to your desired font size */"));
        course_ending_7 = new QLabel(page_2);
        course_ending_7->setObjectName(QStringLiteral("course_ending_7"));
        course_ending_7->setGeometry(QRect(720, 330, 161, 41));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setBold(true);
        font1.setWeight(75);
        course_ending_7->setFont(font1);
        course_ending_7->setStyleSheet(QLatin1String("color: white;\n"
"color: rgb(85, 170, 255);\n"
"font-family: Arial; /* Change \"Arial\" to your desired font family */\n"
"font-size: 34px; /* Change \"14px\" to your desired font size */"));
        course_ending_6 = new QLabel(page_2);
        course_ending_6->setObjectName(QStringLiteral("course_ending_6"));
        course_ending_6->setGeometry(QRect(860, 440, 191, 41));
        course_ending_6->setFont(font1);
        course_ending_6->setStyleSheet(QLatin1String("color: white;\n"
"color: rgb(85, 170, 255);\n"
"font-family: Arial; /* Change \"Arial\" to your desired font family */\n"
"font-size: 34px; /* Change \"14px\" to your desired font size */\n"
""));
        lineEdit_password_3 = new QLineEdit(page_2);
        lineEdit_password_3->setObjectName(QStringLiteral("lineEdit_password_3"));
        lineEdit_password_3->setGeometry(QRect(840, 490, 181, 41));
        pushButton_3 = new QPushButton(page_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(710, 550, 171, 51));
        pushButton_3->setFont(font);
        pushButton_5 = new QPushButton(page_2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(1000, 600, 91, 31));
        pushButton_5->setFont(font);
        lineEdit_password_5 = new QLineEdit(page_2);
        lineEdit_password_5->setObjectName(QStringLiteral("lineEdit_password_5"));
        lineEdit_password_5->setGeometry(QRect(570, 490, 181, 41));
        course_ending_9 = new QLabel(page_2);
        course_ending_9->setObjectName(QStringLiteral("course_ending_9"));
        course_ending_9->setGeometry(QRect(610, 440, 191, 41));
        course_ending_9->setFont(font1);
        course_ending_9->setStyleSheet(QLatin1String("color: white;\n"
"color: rgb(85, 170, 255);\n"
"font-family: Arial; /* Change \"Arial\" to your desired font family */\n"
"font-size: 34px; /* Change \"14px\" to your desired font size */\n"
""));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        label_5 = new QLabel(page_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 0, 1611, 901));
        label_5->setPixmap(QPixmap(QString::fromUtf8("../6706379_3418448 (4).png")));
        label_5->setScaledContents(true);
        label_6 = new QLabel(page_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(350, 160, 911, 611));
        label_6->setPixmap(QPixmap(QString::fromUtf8("../17893271_5931274-removebg-preview (1).png")));
        course_ending_8 = new QLabel(page_3);
        course_ending_8->setObjectName(QStringLiteral("course_ending_8"));
        course_ending_8->setGeometry(QRect(540, 340, 551, 41));
        course_ending_8->setFont(font1);
        course_ending_8->setStyleSheet(QLatin1String("color: white;\n"
"color: rgb(85, 170, 255);\n"
"font-family: Arial; /* Change \"Arial\" to your desired font family */\n"
"font-size: 34px; /* Change \"14px\" to your desired font size */"));
        lineEdit_password_4 = new QLineEdit(page_3);
        lineEdit_password_4->setObjectName(QStringLiteral("lineEdit_password_4"));
        lineEdit_password_4->setGeometry(QRect(660, 410, 271, 51));
        pushButton_4 = new QPushButton(page_3);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(690, 480, 201, 61));
        pushButton_4->setFont(font);
        stackedWidget->addWidget(page_3);

        retranslateUi(Login);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Login", Q_NULLPTR));
        label->setText(QString());
        label_2->setText(QString());
        lineEdit_nom->setPlaceholderText(QString());
        lineEdit_nom_2->setPlaceholderText(QString());
        pushButton->setText(QApplication::translate("Login", "LOGIN", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Login", "R\303\251initialiser le mot de passe", Q_NULLPTR));
        label_7->setText(QApplication::translate("Login", "          WELCOME", Q_NULLPTR));
        label_9->setText(QApplication::translate("Login", "Entrer votre mail", Q_NULLPTR));
        label_10->setText(QApplication::translate("Login", "Entrer votre mot de passe", Q_NULLPTR));
        label_3->setText(QString());
        label_4->setText(QString());
        rolebox_3->clear();
        rolebox_3->insertItems(0, QStringList()
         << QApplication::translate("Login", "Quelle est votre date de naissance ?", Q_NULLPTR)
         << QApplication::translate("Login", "Quel est le titre de votre certification professionnelle la plus r\303\251cente ?", Q_NULLPTR)
         << QApplication::translate("Login", "Quel est le nom de votre superviseur professionnel dans notre entreprise ?", Q_NULLPTR)
         << QApplication::translate("Login", "Quelle est la date \303\240 laquelle vous avez rejoint notre entreprise ?", Q_NULLPTR)
         << QApplication::translate("Login", "Quelle est la sp\303\251cialisation de votre premier dipl\303\264me ?", Q_NULLPTR)
        );
        course_ending_7->setText(QApplication::translate("Login", "Question", Q_NULLPTR));
        course_ending_6->setText(QApplication::translate("Login", "Reponse", Q_NULLPTR));
        lineEdit_password_3->setPlaceholderText(QApplication::translate("Login", "Mot de passe", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("Login", "Confirmer", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("Login", "retourner", Q_NULLPTR));
        lineEdit_password_5->setPlaceholderText(QApplication::translate("Login", "Mot de passe", Q_NULLPTR));
        course_ending_9->setText(QApplication::translate("Login", "Login", Q_NULLPTR));
        label_5->setText(QString());
        label_6->setText(QString());
        course_ending_8->setText(QApplication::translate("Login", "R\303\251initialiser votre mot de passe", Q_NULLPTR));
        lineEdit_password_4->setPlaceholderText(QApplication::translate("Login", "Mot de passe", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("Login", "Confirmer", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
