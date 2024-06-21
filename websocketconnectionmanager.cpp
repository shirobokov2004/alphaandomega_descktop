#include "websocketconnectionmanager.h"

WebSocketConnectionManager::WebSocketConnectionManager(QString url, QObject *parent)
    : QObject{parent}
{
    connect(&m_webSocket, &QWebSocket::connected, this, &WebSocketConnectionManager::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &WebSocketConnectionManager::closed);
    m_webSocket.open(url);
}

void WebSocketConnectionManager::onConnected()
{
    qDebug()<<"connected";
    connect(&m_webSocket, &QWebSocket::binaryMessageReceived, this, &WebSocketConnectionManager::onRecived);
}

void WebSocketConnectionManager::onRecived(const QByteArray &message)
{
    qDebug()<<message.toULongLong();
    m_webSocket.close();
}
