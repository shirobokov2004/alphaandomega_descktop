#include "downdroplineedit.h"

DownDropLineEdit::DownDropLineEdit(QWidget* parent)
    :QLineEdit(parent)
{
    m_searchView = new QListView(this);
    m_searchModel = new QStringListModel(this);
    m_completer = new QCompleter(this);

    m_completer->setCaseSensitivity(Qt::CaseInsensitive);

    m_searchView->setStyleSheet("background-color: #282830; color: rgba(255, 255, 255, 0.60); border: 0px; font-size: 16px; padding: 2px 15px 2px 15px;");
    m_completer->setPopup(m_searchView);
    m_completer->setModel(m_searchModel);

    this->setCompleter(m_completer);
    this->setStyleSheet(m_style);
    connect(this, &QLineEdit::textChanged, this, handleTextChanged);
    connect(m_completer, QOverload<const QString &>::of(&QCompleter::activated), [=](const QString &text){ emit userSelected(text);});
}

DownDropLineEdit::~DownDropLineEdit()
{
    this->deleteLater();
}

void DownDropLineEdit::handleTextChanged(const QString &text)
{
    emit userSearch(text);
}

void DownDropLineEdit::updateCompleter(QStringList userNames)
{
    m_searchModel->setStringList(userNames);
}

