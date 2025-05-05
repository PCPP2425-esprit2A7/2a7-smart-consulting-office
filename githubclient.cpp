#include "githubclient.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QDebug>
#include <QUrl>
#include <QObject>

OpenAIChatBot::OpenAIChatBot(const QString &token) : token(token) {
    networkManager = new QNetworkAccessManager();
    systemPrompt = "You are a helpful AI research assistant for medical professionals. "
                   "You can analyze research descriptions, suggest improvements, and help generate "
                   "new descriptions based on input. Be concise, professional, and accurate.";
    addMessageToHistory("system", systemPrompt);
}

OpenAIChatBot::~OpenAIChatBot() {
    delete networkManager;
}

QString OpenAIChatBot::getResponse(const QString &userMessage, const QString &currentDescription) {
    if (!currentDescription.isEmpty()) {
        QString contextMsg = "The current research description is: \"" + currentDescription + "\"";
        addMessageToHistory("system", contextMsg);
    }

    addMessageToHistory("user", userMessage);
    QJsonObject requestData = createChatCompletionRequest(messageHistory);
    QString response = sendRequest(requestData);
    if (!response.isEmpty() && !response.startsWith("Error:")) {
        addMessageToHistory("assistant", response);
    }

    return response;
}



void OpenAIChatBot::setSystemPrompt(const QString &prompt) {
    systemPrompt = prompt;
    if (!messageHistory.isEmpty() && messageHistory.first().role == "system") {
        messageHistory.first().content = prompt;
    } else {
        clearConversation();
        addMessageToHistory("system", prompt);
    }
}

void OpenAIChatBot::clearConversation() {
    messageHistory.clear();
    addMessageToHistory("system", systemPrompt);
}

QList<QPair<QString, QString>> OpenAIChatBot::getConversationHistory() const {
    QList<QPair<QString, QString>> history;
    for (const Message &msg : messageHistory) {
        if (msg.role != "system") {
            history.append(qMakePair(msg.role, msg.content));
        }
    }
    return history;
}

QJsonObject OpenAIChatBot::createChatCompletionRequest(const QList<Message> &messages) {
    QJsonObject requestObject;
    QJsonArray messagesArray;
    for (const Message &msg : messages) {
        QJsonObject messageObject;
        messageObject["role"] = msg.role;
        messageObject["content"] = msg.content;
        messagesArray.append(messageObject);
    }
    requestObject["messages"] = messagesArray;
    requestObject["model"] = "gpt-4o";
    requestObject["temperature"] = 1.0;
    requestObject["max_tokens"] = 4096;
    requestObject["top_p"] = 1.0;

    return requestObject;
}

QString OpenAIChatBot::sendRequest(const QJsonObject &requestData) {
    QNetworkRequest request(QUrl("https://models.inference.ai.azure.com/chat/completions"));

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader("api-key", token.toUtf8());
    QJsonDocument doc(requestData);
    QByteArray jsonData = doc.toJson();

    qDebug() << "Sending request to Azure inference endpoint";
    qDebug() << "Request data:" << jsonData;

    QNetworkReply *reply = networkManager->post(request, jsonData);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QString response = extractResponseFromReply(reply);
    reply->deleteLater();

    return response;
}

QString OpenAIChatBot::extractResponseFromReply(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Network error:" << reply->errorString();
        qDebug() << "Response data:" << reply->readAll();
        return "Error: " + reply->errorString();
    }

    QByteArray responseData = reply->readAll();
    qDebug() << "Raw response:" << responseData;
    return parseJsonResponse(responseData);
}

QString OpenAIChatBot::parseJsonResponse(const QByteArray &jsonData) {
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (doc.isNull()) {
        qDebug() << "Failed to parse JSON response";
        return "Error: Failed to parse response";
    }

    QJsonObject jsonObj = doc.object();
    if (jsonObj.contains("error")) {
        QJsonObject errorObj = jsonObj["error"].toObject();
        QString errorMessage = errorObj["message"].toString();
        qDebug() << "API error:" << errorMessage;
        return "Error: " + errorMessage;
    }
    if (jsonObj.contains("choices") && jsonObj["choices"].isArray()) {
        QJsonArray choices = jsonObj["choices"].toArray();
        if (!choices.isEmpty()) {
            QJsonObject choice = choices[0].toObject();
            QJsonObject message = choice["message"].toObject();
            return message["content"].toString();
        }
    }

    qDebug() << "Unexpected response format:" << jsonData;
    return "Error: Unexpected response format";
}

void OpenAIChatBot::addMessageToHistory(const QString &role, const QString &content) {
    Message message;
    message.role = role;
    message.content = content;
    messageHistory.append(message);
    if (messageHistory.size() > 10) {
        QList<Message> newHistory;
        for (int i = 0; i < messageHistory.size(); i++) {
            const Message &msg = messageHistory.at(i);
            if (msg.role == "system" || i >= messageHistory.size() - 9) {
                newHistory.append(msg);
            }
        }
        messageHistory = newHistory;
    }
}
