#ifndef GITHUBCLIENT_H
#define GITHUBCLIENT_H

#include <QString>
#include <QList>
#include <QPair>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

class OpenAIChatBot {
public:
    explicit OpenAIChatBot(const QString &token);
    ~OpenAIChatBot();

    QString getResponse(const QString &userMessage, const QString &currentDescription = "");
    void setSystemPrompt(const QString &prompt);
    void clearConversation();
    QList<QPair<QString, QString>> getConversationHistory() const;

private:
    struct Message {
        QString role;
        QString content;

        bool operator==(const Message &other) const {
            return role == other.role && content == other.content;
        }
    };

    QString token;
    QString systemPrompt;
    QList<Message> messageHistory;
    QNetworkAccessManager *networkManager;

    QJsonObject createChatCompletionRequest(const QList<Message> &messages);
    QString sendRequest(const QJsonObject &requestData);
    QString extractResponseFromReply(QNetworkReply *reply);
    QString parseJsonResponse(const QByteArray &jsonData);
    void addMessageToHistory(const QString &role, const QString &content);
};

#endif // GITHUBCLIENT_H
