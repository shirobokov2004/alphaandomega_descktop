#include "loginform.h"

LoginForm::LoginForm(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout* main_layout = new QVBoxLayout(parent);

    QLabel *l_logo = new QLabel("A&O",parent);
    l_logo->setObjectName("l_logo");

    QGroupBox *gb_loginForm = new QGroupBox(parent);
    main_layout->addWidget(l_logo, 0, Qt::AlignHCenter | Qt::AlignTop);
    main_layout->addWidget(gb_loginForm, 1, Qt::AlignHCenter | Qt::AlignVCenter);

    QLabel *l_header = new QLabel("Log in", gb_loginForm);
    l_header->setObjectName("header");

    ClickableLabel *cl_change = new ClickableLabel(gb_loginForm);
    cl_change->setText("Already have account?");
    cl_change->setObjectName("change");

    Input *le_login = new Input(gb_loginForm);
    le_login->setMinimumWidth(430);
    le_login->setObjectName("le_login");
    le_login->setPlaceholderText("login");

    Input *le_password = new Input(gb_loginForm);
    le_password->setPlaceholderText("password");
    le_password->setObjectName("le_password");
    le_password->setMinimumWidth(430);
    le_password->setPassword(true);

    QPushButton *pb_confirm = new QPushButton("Sign In",gb_loginForm);
    pb_confirm->setMinimumWidth(430);

    QVBoxLayout *layout = new QVBoxLayout(gb_loginForm);

    layout->addWidget(l_header,0,Qt::AlignCenter);
    layout->addWidget(le_login,0,Qt::AlignCenter);
    layout->addWidget(le_password,0,Qt::AlignCenter);
    layout->addWidget(pb_confirm,0,Qt::AlignCenter);
    layout->addWidget(cl_change,0,Qt::AlignCenter);
    gb_loginForm->setMinimumSize(530,430);
    gb_loginForm->setMaximumSize(530,430);

    this->setStyleSheet("*{font-family: \"Sansation\"}"
                        "QWidget#centralwidget{background-color: #1F1F21;}"
                        "QLabel#l_logo{color: rgb(224,169,110);font-size: 96px;}"
                        "QGroupBox{border: 3px solid rgb(84,84,84); border-radius: 30px;}"
                        "QGroupBox QLabel#header{color: rgba(255, 255, 255, 0.60); font-size: 32px;}"
                        "QGroupBox QLabel#change{color: rgba(224, 169, 110, 1); font-size: 18px;}"
                        "QGroupBox QLabel#change:hover{color: rgba(255, 255, 255, 0.60);}"
                        "QGroupBox QLineEdit{border: 2px solid rgb(84,84,84); border-radius: 15px; background: #1F1F21; color: rgba(255, 255, 255, 0.6); font-size: 16px; padding: 9px 15px;}"
                        "QGroupBox QPushButton{border: 2px solid rgb(84,84,84); border-radius: 15px; background: #1F1F21; color: rgba(224, 169, 110, 1); font-size: 22px; padding: 5px;}"
                        "QGroupBox QPushButton:hover{border: 2px solid rgba(224, 169, 110, 1);}"
                        "QGroupBox QLineEdit:focus{border: 2px solid rgba(224, 169, 110, 1);}");

}
