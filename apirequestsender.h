#ifndef APIREQUESTSENDER_H
#define APIREQUESTSENDER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QString>

class APIRequestSender : public QObject
{
    Q_OBJECT
public:
    enum RequestType
    {
        GET = 0,
        POST = 1,
        DELETE = 2,
        UPDATE = 3,
        PUT = 4
    };

    explicit APIRequestSender(QObject *parent = nullptr);
    void sendRequest(QString url, QString token = "", RequestType type = RequestType::GET, QByteArray body = "");
signals:
    void requestCompleted(const QJsonDocument& result);
private slots:
    void requestFinished(QNetworkReply* reply);
private:
    QNetworkAccessManager* m_networkManager;
    QNetworkReply* m_networkReply;
};

#endif // APIREQUESTSENDER_H
