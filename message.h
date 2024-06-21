#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QDateTime>
#include <QMenu>
#include <QInputDialog>

class Message : public QWidget
{
    Q_OBJECT
public:
    explicit Message(QString username, QString text, QString time, QWidget* parent);
    ~Message();

public:
    QString getGuid();
    void setGuid(QString guid);
    QString getText();
    void setText(QString text);
    QString getTime();
    void setTime(QString time);
signals:
    void deleteMessage(QString);
    void changeMessage(QString ,QString);
private:
    void handleContextMenuRequested(QPoint pos);
    void handleDeleteMessage();
    void handleChangeMessage();
    QString m_style = "*{background-color: #282830; border-radius: 10px; color: white;}"
                      "QWidget#wrapper > QLabel#messageText{color: #fff;font-size: 14px;}"
                      "QWidget#wrapper > QLabel#messageTime{color: rgba(255, 255, 255, 0.60);font-size: 10px;}"
                      "QWidget#wrapper > QLabel#messageName{font-size: 16px; color: #DDC2A5;}";
    QString m_guid = "";
    QString m_text = "";
    QString m_time = "";
    QMenu *m_contextMenu = nullptr;
    QLabel *m_label = nullptr;
};


#endif // MESSAGE_H
