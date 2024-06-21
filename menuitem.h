#ifndef MENUITEM_H
#define MENUITEM_H

#include <QLabel>
#include <QWidget>
#include <Qt>
#include <QGridLayout>

class MenuItem : public QWidget{
    Q_OBJECT
public:
    explicit MenuItem(QString text,int id,QWidget* parent);
    ~MenuItem();
public:
    void setId(int id);
    int getId();
    void setText(QString text);
    QString getText();
signals:
    void clicked(int id, QString title);
private:
    int m_id = 0;
    QString m_text = "";
protected:
    void mousePressEvent(QMouseEvent* event);
    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent *event);
};

#endif // MENUITEM_H
