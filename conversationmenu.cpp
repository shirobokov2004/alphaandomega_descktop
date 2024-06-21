#include "conversationmenu.h"

ConversationMenu::ConversationMenu(QWidget *parent)
    : QComboBox{parent}
{
    this->addItems(items);
    this->setMaximumSize(150,150);
    this->setStyleSheet("background-color: #282830; border-radius: 10px; color: white;");
}
