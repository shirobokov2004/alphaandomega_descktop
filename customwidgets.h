#ifndef CUSTOMWIDGETS_H
#define CUSTOMWIDGETS_H

#include <QLabel>
#include <QWidget>
#include <Qt>
#include <QGridLayout>

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = nullptr);
    ~ClickableLabel();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);

};

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
};
#endif // CUSTOMWIDGETS_H
