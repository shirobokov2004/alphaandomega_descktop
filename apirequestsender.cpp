#include "apirequestsender.h"

APIRequestSender::APIRequestSender(QObject *parent)
    : QObject{parent}
{
    m_networkManager = new QNetworkAccessManager(this);
    connect(m_networkManager, &QNetworkAccessManager::finished, this, &APIRequestSender::requestFinished);
}

void APIRequestSender::sendRequest(QString url, QString token, RequestType type, QByteArray body)
{
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json");
    if(!token.isEmpty()){
        QString res = "Bearer " + token;
        qDebug()<<url<<res;
        request.setRawHeader("Authorization",res.toLatin1());
    }
    switch(type){
    case RequestType::GET:
        m_networkReply = m_networkManager->get(request);
        break;
    case RequestType::POST:
        m_networkReply = m_networkManager->post(request,body);
        break;
    case RequestType::DELETE:
        m_networkReply = m_networkManager->sendCustomRequest(request, "DELETE", body);
        break;
    case RequestType::UPDATE:
        break;
    case RequestType::PUT:
        m_networkReply = m_networkManager->sendCustomRequest(request, "PUT", body);
        break;
    }
    QEventLoop loop;
    connect(m_networkReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
}

void APIRequestSender::requestFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = reply->readAll();
        QJsonDocument result = QJsonDocument::fromJson(responseData);

        emit requestCompleted(result);
    }
    else
    {
        qDebug() << "Request failed:" << reply->errorString();
    }

    reply->deleteLater();
}
