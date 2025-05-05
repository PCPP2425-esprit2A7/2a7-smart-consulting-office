#include "smsservice.h"
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QDebug>
#include <QRegularExpression>

SmsService::SmsService(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished,
            this, &SmsService::onSmsSent);

    // Initialize with your credentials
    accountSid = "ACb8da91da4b6274592e1a71a56462b8e7";
    authToken = "d853fee5686f861f3eb36d1114f91a3d";
    fromNumber = "+19472162673";
}

SmsService::~SmsService()
{
    delete manager;
}

void SmsService::sendTunisianSms(const QString &phoneNumber, const QString &message)
{
    // Validate Tunisian phone number format
    QRegularExpression tunisianPhoneRegex("^(\\+216|00216)?[2459][0-9]{7}$");
    QString cleanedNumber = phoneNumber;

    cleanedNumber.remove(QRegularExpression("[\\s-]"));

    if (!tunisianPhoneRegex.match(cleanedNumber).hasMatch()) {
        qWarning() << "Invalid Tunisian phone number format:" << phoneNumber;

        return;
    }

    // Format number to E.164
    if (cleanedNumber.startsWith("00216")) {
        cleanedNumber = "+" + cleanedNumber.mid(2);
    }
    else if (cleanedNumber.startsWith("216")) {
        cleanedNumber = "+" + cleanedNumber;
    }
    else if (cleanedNumber.startsWith("0")) {
        cleanedNumber = "+216" + cleanedNumber.mid(1);
    }
    else if (!cleanedNumber.startsWith("+216")) {
        cleanedNumber = "+216" + cleanedNumber;
    }

    QUrl url(QString("https://api.twilio.com/2010-04-01/Accounts/%1/Messages.json").arg(accountSid));
    QNetworkRequest request(url);

    QString auth = QString("%1:%2").arg(accountSid).arg(authToken);
    request.setRawHeader("Authorization", "Basic " + auth.toUtf8().toBase64());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery params;
    params.addQueryItem("To", cleanedNumber);
    params.addQueryItem("From", fromNumber);
    params.addQueryItem("Body", message);

    manager->post(request, params.toString(QUrl::FullyEncoded).toUtf8());
}

void SmsService::onSmsSent(QNetworkReply *reply)
{
    bool success = (reply->error() == QNetworkReply::NoError);
    QString message = success ? "SMS sent successfully" : reply->errorString();


    reply->deleteLater();
}
