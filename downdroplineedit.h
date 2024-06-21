#ifndef DOWNDROPLINEEDIT_H
#define DOWNDROPLINEEDIT_H

#include <QLineEdit>
#include <QListWidget>
#include <QObject>
#include <QWidget>
#include <QWindow>
#include <QGuiApplication>
#include <QScreen>
#include <QCompleter>
#include <QListView>
#include <QStringListModel>

class DownDropLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit DownDropLineEdit(QWidget* parent = nullptr);
    ~DownDropLineEdit();
public slots:
    void handleTextChanged(const QString& text);
    void updateCompleter(QStringList userNames);
signals:
    void userSearch(QString text);
    void userSelected(QString login);
private:
    QString m_style = "QLineEdit {background-color: #282830; color: rgba(255, 255, 255, 0.60); border: 0px; font-size: 16px; padding: 8px 8px 8px 8px;}";
    QCompleter* m_completer = nullptr;
    QListView* m_searchView = nullptr;
    QStringListModel* m_searchModel = nullptr;
};

#endif // DOWNDROPLINEEDIT_H
