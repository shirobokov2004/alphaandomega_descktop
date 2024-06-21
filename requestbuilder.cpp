#include "requestbuilder.h"

RequestBuilder::RequestBuilder(QObject *parent)
    : QObject{parent}
{
    m_sender = new APIRequestSender(this);
}

QJsonObject RequestBuilder::postRegister(QString login, QString password, QString password_confirmation, QString email)
{
    QVariantMap raw;
    raw.insert("login", login);
    raw.insert("password", password);
    raw.insert("password_confirmation", password_confirmation);
    raw.insert("email", email);
    QJsonDocument body = QJsonDocument::fromVariant(raw);
    QJsonObject obj;
    m_connection = QObject::connect(m_sender, &APIRequestSender::requestCompleted, [&](const QJsonDocument& result)
    {
        obj = result.object();
        QObject::disconnect(m_connection);
    });
    m_sender->sendRequest(m_domen + "signup","",APIRequestSender::RequestType::POST, body.toJson());
    return obj;
}

QJsonObject RequestBuilder::postLogin(QString login, QString password)
{
    QVariantMap raw;
    raw.insert("login",login);
    raw.insert("password",password);
    QJsonDocument body = QJsonDocument::fromVariant(raw);
    QJsonObject obj;
    m_connection = QObject::connect(m_sender, &APIRequestSender::requestCompleted, [&](const QJsonDocument& result)
    {
        obj = result.object();
        QObject::disconnect(m_connection);
    });
    m_sender->sendRequest(m_domen + "login","",APIRequestSender::RequestType::POST, body.toJson());
    return obj;
}

QJsonObject RequestBuilder::postCreateConversation(QString token, QString title, QString channel_id, int user_id, QString type)
{
    QVariantMap raw;
    raw.insert("title",title);
    raw.insert("type",type);
    raw.insert("channel_id",channel_id);
    QJsonDocument body = QJsonDocument::fromVariant(raw);
    QJsonObject obj;
    m_connection = QObject::connect(m_sender, &APIRequestSender::requestCompleted, [&](const QJsonDocument& result)
    {
        obj = result.object();
        QObject::disconnect(m_connection);
    });
    m_sender->sendRequest(m_domen + "conversations/" + QString::number(user_id), token, APIRequestSender::RequestType::POST, body.toJson());
    return obj;
}

QJsonObject RequestBuilder::postSendMessage(QString token, int id_conversation, int sender_id, int messages_type_id, QString messages)
{
    QVariantMap raw;
    raw.insert("id_conversation",id_conversation);
    raw.insert("sender_id",sender_id);
    raw.insert("messages_type_id",messages_type_id);
    raw.insert("messages",messages);
    QJsonDocument body = QJsonDocument::fromVariant(raw);
    QJsonObject obj;
    m_connection = QObject::connect(m_sender, &APIRequestSender::requestCompleted, [&](const QJsonDocument& result)
    {
        obj = result.object();
        QObject::disconnect(m_connection);
    });
    m_sender->sendRequest(m_domen + "messages",token ,APIRequestSender::RequestType::POST, body.toJson());
    return obj;
}

QJsonObject RequestBuilder::postSearchUsers(QString login, QString token)
{
    QVariantMap raw;
    raw.insert("login",login);
    QJsonDocument body = QJsonDocument::fromVariant(raw);
    QJsonObject obj;
    m_connection = QObject::connect(m_sender, &APIRequestSender::requestCompleted, [&](const QJsonDocument& result)
    {
        obj = result.object();
        QObject::disconnect(m_connection);
    });
    m_sender->sendRequest(m_domen + "users/search",token,APIRequestSender::RequestType::POST, body.toJson());
    return obj;
}

QJsonObject RequestBuilder::postAddParticipant(QString token, int conversation_id, int user_id, int role_id)
{
    QVariantMap raw;
    raw.insert("conversation_id",conversation_id);
    raw.insert("user_id", QVariant(user_id).toList());
    raw.insert("role_id",role_id);
    QJsonDocument body = QJsonDocument::fromVariant(raw);
    qDebug()<<raw;
    QJsonObject obj;
    m_connection = QObject::connect(m_sender, &APIRequestSender::requestCompleted, [&](const QJsonDocument& result)
    {
        obj = result.object();
        QObject::disconnect(m_connection);
    });
    m_sender->sendRequest(m_domen + "participant", token, APIRequestSender::RequestType::POST, body.toJson());
    return obj;
}

QJsonObject RequestBuilder::postAddFriend(QString token, QString login)
{
    QVariantMap raw;
    raw.insert("login",login);
    QJsonDocument body = QJsonDocument::fromVariant(raw);
    QJsonObject obj;
    m_connection = QObject::connect(m_sender, &APIRequestSender::requestCompleted, [&](const QJsonDocument& result)
    {
        obj = result.object();
        QObject::disconnect(m_connection);
    });
    m_sender->sendRequest(m_domen + "friend", token, APIRequestSender::RequestType::POST, body.toJson());
    return obj;
}

QJsonObject RequestBuilder::deleteMessage(QString token, QString guid)
{
    QVariantMap raw;
    raw.insert("message_guid",guid);
    QJsonDocument body = QJsonDocument::fromVariant(raw);
    QJsonObject obj;
    m_connection = QObject::connect(m_sender, &APIRequestSender::requestCompleted, [&](const QJsonDocument& result)
    {
        obj = result.object();
        QObject::disconnect(m_connection);
    });
    m_sender->sendRequest(m_domen + "messages", token, APIRequestSender::RequestType::DELETE, body.toJson());
    return obj;
}

QJsonObject RequestBuilder::deleteConversation(QString token, int conversation_id)
{
    QJsonObject obj;
    m_connection = QObject::connect(m_sender, &APIRequestSender::requestCompleted, [&](const QJsonDocument& result)
    {
        obj = result.object();
        QObject::disconnect(m_connection);
    });
    m_sender->sendRequest(m_domen + "conversations/" + QString::number(conversation_id), token, APIRequestSender::RequestType::DELETE);
    return obj;
}

QJsonObject RequestBuilder::updateMessage(QString token, QString guid, QString message)
{
    QVariantMap raw;
    raw.insert("message_guid",guid);
    raw.insert("messages",message);
    QJsonDocument body = QJsonDocument::fromVariant(raw);
    QJsonObject obj;
    m_connection = QObject::connect(m_sender, &APIRequestSender::requestCompleted, [&](const QJsonDocument& result)
    {
        obj = result.object();
        QObject::disconnect(m_connection);
    });
    m_sender->sendRequest(m_domen + "messages", token, APIRequestSender::RequestType::PUT, body.toJson());
    return obj;
}

QJsonObject RequestBuilder::addParticipant(QString token, int conversation_id, int user_id, int role_id)
{
    QVariantMap raw;
    raw.insert("conversation_id",conversation_id);
    QVariantList list;
    list.append(user_id);
    raw.insert("user_id", list);
    raw.insert("role_id",role_id);
    QJsonDocument body = QJsonDocument::fromVariant(raw);
    qDebug()<<body.toJson();
    QJsonObject obj;
    m_connection = QObject::connect(m_sender, &APIRequestSender::requestCompleted, [&](const QJsonDocument& result)
    {
        obj = result.object();
        QObject::disconnect(m_connection);
    });
    m_sender->sendRequest(m_domen + "participant", token, APIRequestSender::RequestType::POST, body.toJson());
    return obj;
}

QJsonObject RequestBuilder::updateConversationName(QString token, int conversation_id, QString name)
{
    QVariantMap raw;
    raw.insert("title",name);
    QJsonDocument body = QJsonDocument::fromVariant(raw);
    QJsonObject obj;
    m_connection = QObject::connect(m_sender, &APIRequestSender::requestCompleted, [&](const QJsonDocument& result)
    {
        obj = result.object();
        QObject::disconnect(m_connection);
    });
    m_sender->sendRequest(m_domen + "conversations/" + QString::number(conversation_id), token, APIRequestSender::RequestType::PUT, body.toJson());
    return obj;
}

QJsonObject RequestBuilder::updateStatus(QString token, QString status, QString login)
{
    QVariantMap raw;
    raw.insert("login",login);
    raw.insert("status",status);
    QJsonDocument body = QJsonDocument::fromVariant(raw);
    QJsonObject obj;
    m_connection = QObject::connect(m_sender, &APIRequestSender::requestCompleted, [&](const QJsonDocument& result)
    {
        obj = result.object();
        QObject::disconnect(m_connection);
    });
    m_sender->sendRequest(m_domen + "friend", token, APIRequestSender::RequestType::PUT, body.toJson());
    return obj;
}

QJsonObject RequestBuilder::getUser(QString token)
{
    QJsonObject obj;
    m_connection = QObject::connect(m_sender, &APIRequestSender::requestCompleted, [&](const QJsonDocument& result)
    {
        obj = result.object();
        QObject::disconnect(m_connection);
    });
    m_sender->sendRequest(m_domen + "user", token);
    return obj;
}

QJsonArray RequestBuilder::getMessage(int conversation_id,QString token)
{
    QJsonArray arr;
    m_connection = QObject::connect(m_sender, &APIRequestSender::requestCompleted, [&](const QJsonDocument& result)
    {
        arr = result.array();
        QObject::disconnect(m_connection);
    });
    m_sender->sendRequest(QString(m_domen + "messages/%1").arg(conversation_id), token);
    return arr;
}

QJsonArray RequestBuilder::getConversations(QString token, int id)
{
    QJsonArray arr;
    m_connection = QObject::connect(m_sender, &APIRequestSender::requestCompleted, [&](const QJsonDocument& result)
    {
        arr = result.array();
        QObject::disconnect(m_connection);
    });
    m_sender->sendRequest(QString(m_domen + "conversations/%1").arg(id),token);
    return arr;
}

QJsonArray RequestBuilder::getFriends(QString token)
{
    QJsonArray obj;
    m_connection = QObject::connect(m_sender, &APIRequestSender::requestCompleted, [&](const QJsonDocument& result)
    {
        obj = result.array();
        QObject::disconnect(m_connection);
    });
    m_sender->sendRequest(m_domen + "friend/accepted", token);
    return obj;
}

QJsonArray RequestBuilder::getDeclinedFriends(QString token)
{
    QJsonArray obj;
    m_connection = QObject::connect(m_sender, &APIRequestSender::requestCompleted, [&](const QJsonDocument& result)
    {
        obj = result.array();
        QObject::disconnect(m_connection);
    });
    m_sender->sendRequest(m_domen + "friend/declined", token);
    return obj;
}

QJsonArray RequestBuilder::getWaitingFriends(QString token)
{
    QJsonArray obj;
    m_connection = QObject::connect(m_sender, &APIRequestSender::requestCompleted, [&](const QJsonDocument& result)
    {
        obj = result.array();
        QObject::disconnect(m_connection);
    });
    m_sender->sendRequest(m_domen + "friend/waiting", token);
    return obj;
}
