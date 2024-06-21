#include "message.h"

Message::Message(QString username, QString text, QString time, QWidget* parent)
    :QWidget(parent)
{
    this->setObjectName("message");
    QWidget *wrapper = new QWidget(this);
    QVBoxLayout *p_lay = new QVBoxLayout(this);
    p_lay->addWidget(wrapper);
    wrapper->setObjectName("wrapper");
    QVBoxLayout *layout = new QVBoxLayout(wrapper);

    QLabel *name = new QLabel(username, wrapper);
    name->setObjectName("messageName");

    m_text = text;
    m_label = new QLabel(text, wrapper);
    m_label->setWordWrap(wrapper);
    m_label->setMaximumWidth(500);
    m_label->setMinimumHeight(m_label->heightForWidth(500)+15);
    m_label->setObjectName("messageText");

    QDateTime dt = QDateTime::fromString(time,Qt::ISODate);
    QString t = dt.time().toString();
    t.chop(3);
    QLabel *messageTime = new QLabel(t, wrapper);
    messageTime->setObjectName("messageTime");
    layout->addWidget(name);
    layout->addWidget(m_label);
    layout->addWidget(messageTime,1,Qt::AlignRight);

    m_contextMenu = new QMenu(this);
    QAction *action_delete = new QAction("Delete message", wrapper);
    QAction *action_change = new QAction("Change message", wrapper);
    m_contextMenu->addAction(action_change);
    m_contextMenu->addAction(action_delete);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    m_contextMenu->setStyleSheet("font-size: 16px;");

    this->setStyleSheet(m_style);
    connect(action_delete, &QAction::triggered, this, &Message::handleDeleteMessage);
    connect(action_change, &QAction::triggered, this, &Message::handleChangeMessage);
    connect(this, &QWidget::customContextMenuRequested, this, &Message::handleContextMenuRequested);
}

Message::~Message()
{
    this->deleteLater();
}

QString Message::getGuid()
{
    return m_guid;
}

void Message::setGuid(QString guid)
{
    m_guid = guid;
}

QString Message::getText()
{
    return m_text;
}

void Message::setText(QString text)
{
    m_text = text;
}

QString Message::getTime()
{
    return m_time;
}

void Message::setTime(QString time)
{
    m_time = time;
}

void Message::handleContextMenuRequested(QPoint pos)
{
    m_contextMenu->popup(this->mapToGlobal(pos));
}

void Message::handleDeleteMessage()
{
    emit deleteMessage(m_guid);
    this->deleteLater();
}

void Message::handleChangeMessage()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Change message"),
                                             tr("Change message"), QLineEdit::Normal,
                                             m_text ,&ok);
    if(ok && !text.isEmpty()){
        emit changeMessage(m_guid ,text);
        m_label->setText(text);
    }
}


