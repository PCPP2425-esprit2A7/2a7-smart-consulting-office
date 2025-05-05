#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "consultants.h"
#include "arduino.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

signals:
    void loginSuccessful();
private slots:
    void attemptLogin();
    //void update_label();
   // void switchToMainWindow(); // Slot to handle switching to the main window


private:
    Ui::Login *ui;
    Arduino A;
    QString data;
    bool validateConsultantCredentials(const QString &email, const QString &password, consultants &consultant);
    void navigateToPage2();
    void navigateToPage1();

    void checkAnswer();
    void changePassword();
    int getConsultantIDByQuestionAndAnswer(const QString& question, const QString& answer) const;
    bool passwordExists(const QString& password);


};

#endif // LOGIN_H
