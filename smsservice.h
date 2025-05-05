#ifndef SMSSERVICE_H
#define SMSSERVICE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class SmsService : public QObject
{
    Q_OBJECT

public:
    explicit SmsService(QObject *parent = nullptr);
    ~SmsService() override;

    void sendTunisianSms(const QString &phoneNumber, const QString &message);


signals:
    void smsSent(bool success, const QString &message);

private:
    QNetworkAccessManager *manager;
    QString accountSid;
    QString authToken;
    QString fromNumber;

private slots:
    void onSmsSent(QNetworkReply *reply);
};

#endif // SMSSERVICE_H
