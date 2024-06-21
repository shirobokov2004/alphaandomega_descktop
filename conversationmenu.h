#ifndef CONVERSATIONMENU_H
#define CONVERSATIONMENU_H

#include <QComboBox>
#include <QObject>
#include <QWidget>

class ConversationMenu : public QComboBox
{
    Q_OBJECT
public:
    ConversationMenu(QWidget *parent = nullptr);
private:
    QStringList items = {"Menu", "Add participant", "Delete conversation", "Change name"};
};

#endif // CONVERSATIONMENU_H
