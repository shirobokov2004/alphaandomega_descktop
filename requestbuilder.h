#ifndef REQUESTBUILDER_H
#define REQUESTBUILDER_H

#include <QObject>
#include <apirequestsender.h>
#include <stdarg.h>
#include <QList>

class RequestBuilder : public QObject
{
    Q_OBJECT

public:
    explicit RequestBuilder(QObject *parent = nullptr);

    //POST request
    QJsonObject postRegister(QString login, QString password, QString password_confirmation, QString email);
    QJsonObject postLogin(QString login, QString password);
    QJsonObject postCreateConversation(QString token, QString title, QString channel_id, int user_id, QString type);
    QJsonObject postSendMessage(QString token, int id_conversation, int sender_id, int messages_type_id, QString messages);
    QJsonObject postSearchUsers(QString login, QString token);
    QJsonObject postAddParticipant(QString token, int conversation_id, int user_id, int role_id);
    QJsonObject postAddFriend(QString token, QString login);

    //GET request
    QJsonObject getUser(QString token);
    QJsonArray getMessage(int conversation_id,QString token);
    QJsonArray getConversations(QString token, int id);
    QJsonObject getParticipants();
    QJsonArray getFriends(QString token);
    QJsonArray getDeclinedFriends(QString token);
    QJsonArray getWaitingFriends(QString token);

    //DELETE request
    QJsonObject deleteMessage(QString token, QString guid);
    QJsonObject deleteConversation(QString token, int conversation_id);

    //UPDATE request
    QJsonObject updateMessage(QString token, QString guid, QString message);
    QJsonObject addParticipant(QString token, int conversation_id, int user_id, int role_id);
    QJsonObject updateConversationName(QString token, int conversation_id,QString name);
    QJsonObject updateStatus(QString token, QString status,  QString login);

//    QJsonDocument boduBuilder(int c, ...);

private:
    APIRequestSender *m_sender = nullptr;
    QMetaObject::Connection m_connection;
    QString m_domen = "http://vergil.ru/api/";
};

#endif // REQUESTBUILDER_H
