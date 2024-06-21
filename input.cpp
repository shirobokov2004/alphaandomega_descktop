#include "input.h"

Input::Input(QWidget *parent)
    :QLineEdit(parent)
{
    this->setStyleSheet(m_style);
}

Input::~Input()
{
    this->deleteLater();
}

bool Input::isPassword()
{
    if(this->echoMode() == QLineEdit::Password)
        return true;
    else
        return false;
}

void Input::setPassword(bool b)
{
    if(b)
        this->setEchoMode(QLineEdit::Password);
    else
        this->setEchoMode(QLineEdit::NoEcho);
}
