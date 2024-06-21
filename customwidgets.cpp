#include "customwidgets.h"

ClickableLabel::ClickableLabel(QWidget* parent)
    : QLabel(parent) {

}
ClickableLabel::~ClickableLabel() {
    this->deleteLater();
}
void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    emit clicked();
}

//////////////////////////////////////////////////////////////

MenuItem::MenuItem(QString text,int id,QWidget* parent)
    :QWidget(parent){
    this->setMaximumSize(430,70);
    this->setMinimumSize(430,70);
    this->setObjectName("menuItem");

    QGridLayout *layout_menuItem = new QGridLayout(this);
    QLabel *l_name = new QLabel(text ,this);
    layout_menuItem->addWidget(l_name,1,1);

    m_text = text;
    m_id = id;
    this->setStyleSheet("QWidget#menuItem {background-color: #1F1F21; color: #fff; border: 0px;}"
                        "QWidget#menuItem QLabel {color: #fff;}"
                        "QWidget#menuItem:hover {background-color: #DDC2A5; color: #000;}");
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

//////////////////////////////////////////////////////////////
