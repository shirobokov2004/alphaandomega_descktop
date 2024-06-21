#ifndef MENU_H
#define MENU_H

#include <QObject>
#include <QWidget>
#include <QStringListModel>

class Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = nullptr);

signals:
private:
    QStringListModel *m_model = nullptr;
};

#endif // MENU_H
