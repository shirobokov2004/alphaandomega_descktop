#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <clickablelabel.h>
#include <input.h>
#include <QPushButton>

class LoginForm : public QWidget
{
    Q_OBJECT
public:
    explicit LoginForm(QWidget *parent = nullptr);

signals:

};

#endif // LOGINFORM_H
