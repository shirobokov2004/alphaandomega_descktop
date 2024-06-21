#include "menu.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QListView>

Menu::Menu(QWidget *parent)
    : QWidget{parent}
{
    this->setStyleSheet("border:1px solid red;");
    QListView *view = new QListView(this);
    QStringList l = { "Arial", "Helvetica", "Times", "Helvetica", "Times", "Helvetica", "Times", "Helvetica", "Times", "Helvetica", "Times", "Helvetica", "Times", "Helvetica", "Times" };
    m_model = new QStringListModel(this);
    m_model->setStringList(l);
    view->setModel(m_model);
    qDebug()<<"menu created";
}
