#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "usersession.h"
#include "consultants.h"
#include "connection.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QTextStream>
#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <QComboBox>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QAxObject>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QVBoxLayout>
#include <QtCharts>
#include<QDate>
#include <QDoubleSpinBox>
#include <QAxObject>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QKeyEvent>
#include <QtCharts/QChart>
#include <QSqlError>


Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);//pour initialiser tous les composentes
    int verif_arduino = A.connect_arduino();
                switch(verif_arduino){
                case(0):qDebug()<<"arduino is available and connected to :" << A.getArduinoPortName();
                    break;
                case(1):qDebug()<<"arduino is available but not connected to :" << A.getArduinoPortName();
                    break;
                case(-1):qDebug()<<"arduino is not available" ;
                    break;
                }
            QObject::connect(A.getSerial(),SIGNAL(readyRead()),this,SLOT(update_label()));
    // Establish database connection
    Connection conn;
    if (!conn.createconnect()) {
        QMessageBox::critical(this, "Database Error",
                            "Failed to connect to database.\n"
                            "Please check your ODBC configuration and try again.");
        return;
    }

    // Rest of your existing constructor code
    connect(ui->pushButton, &QPushButton::clicked, this, &Login::attemptLogin);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Login::navigateToPage2);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &Login::navigateToPage1);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &Login::checkAnswer);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &Login::changePassword);

    ui->lineEdit_nom_2->setEchoMode(QLineEdit::Password);
}
Login::~Login()
{
    delete ui;
}
void Login::update_label()
{
    data += A.readFromArduino();
    qDebug() << "Données reçues d'Arduino :" << data;

    int newlineIndex = data.indexOf('\n');
    if (newlineIndex != -1) {
        QString message = data.left(newlineIndex).trimmed();  // Trim for safety
        data = "";  // Clear buffer

        // Set ID field or store in a variable
        ui->lineEdit_nom_2->setText(message);  // Assuming you have a QLineEdit named idField
        QMessageBox::information(this, "Info", "password reçu, cliquez sur Connexion");
    }
}


void Login::attemptLogin()//récupères l'email et le mot de passe saisis
{
    QString email = ui->lineEdit_nom->text();
    QString password = ui->lineEdit_nom_2->text();

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        Connection conn;
        if (!conn.createconnect()) {
            QMessageBox::warning(this, "Database Error",
                               "Database connection lost. Please try again.");
            return;
        }
    }

    consultants consultant;
    if (validateConsultantCredentials(email, password, consultant)) {
        UserSession::instance().setConsultant(
            consultant.getID_CONS(),
            consultant.getNom(),
            consultant.getPrenom(),
            consultant.getEmail(),
            consultant.getTel(),
            consultant.getCategorie(),
            consultant.getMdp(),
            consultant.getHeures(),
            consultant.getQuestion(),
            consultant.getReponse()
        );

        qDebug() << "Logged in as consultant:" << consultant.getNom() << consultant.getPrenom();
        qDebug() << "Category:" << consultant.getCategorie();

        // Send success to Arduino
        A.write_arduino(consultant.getNom().toUtf8());

        // Always navigate to page 0 (index 0)
        ui->stackedWidget->setCurrentIndex(0);

        // Store the category in UserSession for later use
        UserSession::instance().setCategory(consultant.getCategorie());
        emit loginSuccessful();
        accept();
        QSqlDatabase::removeDatabase("qt_sql_default_connection");

        MainWindow *mainWindow = new MainWindow();
        mainWindow->show();
    } else {
        QMessageBox::warning(this, tr("Login Failed"),
                           tr("Invalid email or password. Please try again."));

        // Send failure to Arduino
        A.write_arduino("non\n");
    }
}


bool Login::validateConsultantCredentials(const QString &email, const QString &password, consultants &consultant)
{
    QSqlQuery query;
    query.prepare("SELECT ID_CONS, NOM_CONS, PRENOM_CONS, EMAIL, TEL, CATEGORIE, MDP, HEURES, QUESTION, REPONSE "
                 "FROM consultants WHERE EMAIL = :email AND MDP = :password");
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Login query error:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        // Populate the consultant object with data from the database
        consultant.setID_CONS(query.value(0).toInt());
        consultant.setNom(query.value(1).toString());
        consultant.setPrenom(query.value(2).toString());
        consultant.setEmail(query.value(3).toString());
        consultant.setTel(query.value(4).toInt());
        consultant.setCategorie(query.value(5).toString());
        consultant.setMdp(query.value(6).toString());
        consultant.setHeures(query.value(7).toInt());
        consultant.setQuestion(query.value(8).toString());
        consultant.setReponse(query.value(9).toString());

        return true;
    }

    return false;
}



void Login::navigateToPage2()
{
    // Navigate to page 2 of the stacked widget
    ui->stackedWidget->setCurrentIndex(1); // Assuming page 2 has index 1
}
void Login::navigateToPage1()
{
    // Navigate to page 2 of the stacked widget
    ui->stackedWidget->setCurrentIndex(0); // Assuming page 2 has index 1
}
void Login::checkAnswer()
{
    // Get the selected question, entered answer, and email (instead of login)
    QString selectedQuestion = ui->rolebox_3->currentText();
    QString enteredAnswer = ui->lineEdit_password_3->text();
    QString enteredEmail = ui->lineEdit_password_5->text();

    // Query the database to check if the question, answer, and email match any record
    Connection conn;
    if (!conn.createconnect()) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to connect to the database!"));
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM consultants WHERE QUESTION = :question AND REPONSE = :answer AND EMAIL = :email");
    query.bindValue(":question", selectedQuestion);
    query.bindValue(":answer", enteredAnswer);
    query.bindValue(":email", enteredEmail);

    if (query.exec() && query.next()) {
        // If a record is found, navigate to page 3
        ui->stackedWidget->setCurrentIndex(2); // Assuming page 3 has index 2
    } else {
        // If no matching record is found, show a popup indicating wrong answer
        QMessageBox::warning(this, tr("Wrong Answer"), tr("The answer or email is incorrect. Please try again."));
    }

    conn.closeconnection();
}

void Login::changePassword()
{
    // Get the new password entered by the user
    QString newPassword = ui->lineEdit_password_4->text();

    // Validate the new password
    QRegularExpression passwordRegex("^(?=.*[A-Z])(?=.*[0-9]).{8,}$");
    if (!passwordRegex.match(newPassword).hasMatch()) {
        QMessageBox::warning(this, tr("Invalid Password"), tr("Password must contain at least one uppercase letter and one number, and be at least 8 characters long."));
        return;
    }

    // Check if the new password is already taken
    if (passwordExists(newPassword)) {
        QMessageBox::critical(this, tr("Error"), tr("This password is already taken. Please choose a different one."));
        return;
    }

    // Get the question and answer entered by the user
    QString question = ui->rolebox_3->currentText();
    QString answer = ui->lineEdit_password_3->text();

    // Get the consultant ID based on the provided question and answer
    int currentConsultantID = getConsultantIDByQuestionAndAnswer(question, answer);
    if (currentConsultantID == -1) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to retrieve consultant ID based on question and answer."));
        return;
    }

    // Update the password in the database for the current consultant
    Connection conn;
    if (!conn.createconnect()) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to connect to the database!"));
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE consultants SET MDP = :password WHERE ID_CONS = :id_cons");
    query.bindValue(":password", newPassword);
    query.bindValue(":id_cons", currentConsultantID);

    if (!query.exec()) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to update password in the database!"));
        return;
    }

    conn.closeconnection();

    // Navigate the user back to the appropriate page in the stacked widget
    ui->stackedWidget->setCurrentIndex(0); // Assuming the main page has index 0

    // Display a message to indicate that the password has been changed
    QMessageBox::information(this, tr("Password Changed"), tr("Your password has been successfully changed."));
}

bool Login::passwordExists(const QString& password)
{
    // Check if the provided password already exists in the database
    Connection conn;
    if (!conn.createconnect()) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to connect to the database!"));
        return true; // Consider it as taken to prevent further action
    }

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM consultants WHERE MDP = :password");
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return count > 0; // If count is greater than 0, the password already exists
    }

    conn.closeconnection();
    return true; // Consider it as taken to prevent further action in case of an error
}

int Login::getConsultantIDByQuestionAndAnswer(const QString& question, const QString& answer) const
{
    // Query the database to retrieve the consultant ID based on the provided question and answer
    Connection conn;
    if (!conn.createconnect()) {
        QMessageBox::critical(nullptr, tr("Error"), tr("Failed to connect to the database!"));
        return -1; // Return -1 to indicate an error
    }

    QSqlQuery query;
    query.prepare("SELECT ID_CONS FROM consultants WHERE QUESTION = :question AND REPONSE = :answer");
    query.bindValue(":question", question);
    query.bindValue(":answer", answer);
    if (!query.exec()) {
        QMessageBox::critical(nullptr, tr("Error"), tr("Failed to connect to the database!"));
        return -1; // Return -1 to indicate an error
    }

    int consultantID = -1; // Initialize consultantID to -1 (indicating failure)
    if (query.next()) {
        consultantID = query.value(0).toInt(); // Retrieve the consultant ID from the query result
    }

    conn.closeconnection();

    return consultantID; // Return the consultant ID
}
