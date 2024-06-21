#include "menuitem.h"

MenuItem::MenuItem(QString text,int id,QWidget* parent)
    :QWidget(parent){
//    this->setMaximumSize(415,70);
//    this->setMinimumSize(415,70);
    this->setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred));
    this->setContentsMargins(0,0,0,0);
    this->setObjectName("menuItem");
    m_text = text;
    m_id = id;

    QGridLayout *layout_menuItem = new QGridLayout(this);
    QLabel *l_name = new QLabel(text ,this);

    layout_menuItem->addWidget(l_name);
    layout_menuItem->setSpacing(0);
    layout_menuItem->setContentsMargins(0,0,0,0);

    this->setStyleSheet("background-color: #1F1F21; color: #FFF; border: 0px; font-size: 18px;");

}
MenuItem::~MenuItem(){
    this->deleteLater();
}
void MenuItem::setId(int id){
    m_id = id;
}
int MenuItem::getId(){
    return m_id;
}
void MenuItem::setText(QString text){
    m_text = text;
}
QString MenuItem::getText(){
    return m_text;
}

void MenuItem::mousePressEvent(QMouseEvent *event){
    emit clicked(m_id, m_text);
}

void MenuItem::enterEvent(QEnterEvent *event)
{
    this->setStyleSheet("background-color: #DDC2A5; border: 0px; font-size: 18px;");
}

void MenuItem::leaveEvent(QEvent *event)
{
    this->setStyleSheet("background-color: #1F1F21; color: #FFF; border: 0px; font-size: 18px;");
}

