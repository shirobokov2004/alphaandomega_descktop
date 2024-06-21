#ifndef WEBSOCKETCONNECTIONMANAGER_H
#define WEBSOCKETCONNECTIONMANAGER_H

#include <QObject>
#include <QWebSocket>

class WebSocketConnectionManager : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketConnectionManager(QString url,QObject *parent = nullptr);

signals:
    void closed();

private slots:
    void onConnected();
    void onRecived(const QByteArray &message);

private:
    QWebSocket m_webSocket;
};

#endif // WEBSOCKETCONNECTIONMANAGER_H
