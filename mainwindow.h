#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <requestbuilder.h>
#include <menuitem.h>
#include <clickablelabel.h>
#include <message.h>
#include <input.h>
#include <popup.h>
#include <downdroplineedit.h>
#include <menu.h>
#include <conversationmenu.h>
#include <frienddialog.h>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>

#include <QGroupBox>
#include <QListWidget>
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QScrollArea>
#include <QUiLoader>
#include <QFile>
#include <QUuid>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    class Style{
    public:
        inline static const QString login_reg = "*{font-family: \"Sansation\"}"
                                  "QWidget#parent{background-color: #1F1F21;}"
                                  "QLabel#l_logo{color: rgb(224,169,110);font-size: 96px;}"
                                  "QGroupBox{border: 3px solid rgb(84,84,84); border-radius: 30px;}"
                                  "QGroupBox QLabel#header{color: rgba(255, 255, 255, 0.60); font-size: 32px;}"
                                  "QGroupBox QLabel#change{color: rgba(224, 169, 110, 1); font-size: 18px;}"
                                  "QGroupBox QLabel#change:hover{color: rgba(255, 255, 255, 0.60);}"
                                  "QGroupBox QLineEdit{border: 2px solid rgb(84,84,84); border-radius: 15px; background: #1F1F21; color: rgba(255, 255, 255, 0.6); font-size: 16px; padding: 9px 15px;}"
                                  "QGroupBox QPushButton{border: 2px solid rgb(84,84,84); border-radius: 15px; background: #1F1F21; color: rgba(224, 169, 110, 1); font-size: 22px; padding: 5px;}"
                                  "QGroupBox QPushButton:hover{border: 2px solid rgba(224, 169, 110, 1);}"
                                  "QGroupBox QLineEdit:focus{border: 2px solid rgba(224, 169, 110, 1);}";
        inline static const QString main = "*{font-family: \"Sansation\"; margin: 0px; padding: 0px;}"
                                           "QWidget#centralwidget{background-color: #1F1F21;}"
                                           "QGroupBox#mainMenu{background-color: #1F1F21; border: 0px; border-right: 2px solid #545454;}"
                                           "QGroupBox#mainMenu QPushButton {background-color: #1F1F21; color: #fff; height: 80px; border: 0px;}"
                                           "QGroupBox#mainMenu QLabel{color: #E0A96E; font-size: 32px; border-bottom: 2px solid #545454;}"
                                           "QGroupBox#mainMenu QPushButton:hover{background-color: #DDC2A5; color: #000;}"
                                           ""
                                           "QWidget#auxMenu {background-color: #1F1F21; border-right: 2px solid #545454;}"
//                                           "QScrollArea#auxMenu QLineEdit {background-color: #282830; color: rgba(255, 255, 255, 0.60); border: 0px; border-radius: 15px; font-size: 16px; padding: 8px 8px 8px 8px;}"
                                           "QWidget#auxMenu QWidget#itemWrapper{background-color: #1F1F21; border:0px ;}"
                                           "QWidget#auxMenu QScrollArea{background-color: #1F1F21; border:0px ;}"
                                           "QWidget#auxMenu QPushButton#pb_createConversation{background-color: #1F1F21; color: #fff; height: 50px; border: 0px;font-size: 18px;}"
                                           "QWidget#auxMenu QPushButton#pb_createConversation:hover{background-color: #DDC2A5; color: #000;}"
                                           ""
                                           "QGroupBox#workSpace{background-color: #1F1F21; border: 0px;}"
                                           "QGroupBox#workSpace QWidget#header QLabel{color: rgba(255, 255, 255, 0.60); font-size: 12px;}"
                                           "QGroupBox#workSpace QWidget#header QLabel#title {color: #FFF; font-size: 16px;}"
                                           "QGroupBox#workSpace QScrollArea{border: 0px;}"
                                           "QGroupBox#workSpace QWidget#messageStore{background-color: #1B1B1B; border: 0px;}"
                                           "QGroupBox#workSpace QLineEdit#messageInput{padding: 10px; background-color: #1F1F21;border: 0px; border-top: 2px solid #545454; color: rgba(255, 255, 255, 0.60);}"
                                           "QInputDialog {background-color: #282830; color: white;}";
    };
    class User{
    public:
        int getId()                             {return this->id;}
        void setId(int id)                      {this->id = id;}
        int getPhone()                          {return this->phone;}
        void setPhone(int phone)                {this->phone = phone;}
        QString getEmail()                      {return this->email;}
        void setEmail(QString email)            {this->email = email;}
        QString getFirstName()                  {return this->first_name;}
        void setFirstName(QString first_name)   {this->first_name = first_name;}
        QString getLastName()                   {return this->last_name;}
        void setLastName(QString last_name)     {this->last_name = last_name;}
        QString getMiddleName()                 {return this->middle_name;}
        void setMiddleName(QString middle_name) {this->middle_name = middle_name;}
        QString getLogin()                      {return this->login;}
        void setLogin(QString login)            {this->login = login;}
        QString getAvatar()                     {return this->avatar;}
        void setAvatar(QString avatar)          {this->avatar = avatar;}
        bool getIsActive()                      {return this->is_active;}
        void setIsActive(bool is_active)        {this->is_active = is_active;}
        bool getIsBlocked()                     {return this->is_blocked;}
        void setIsBlocked(bool is_blocked)      {this->is_blocked = is_blocked;}
        int getStatusId()                       {return this->status_id;}
        void setStatusId(int status_id)         {this->status_id = status_id;}
        QString getToken()                      {return this->token;}
        void setToken(QString token)            {this->token = token;}
    private:
        int id = 0;
        int phone = 0;
        QString email = "";
        QString first_name = "";
        QString last_name = "";
        QString middle_name = "";
        QString login = "";
        QString avatar = "";
        bool is_blocked = false;
        bool is_active = false;
        int status_id = 0;
        QString token = "";
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void restoreSettings();
    void writeUserToken(QString token);

    void setupRegWin();
    void setupLoginWin();
    void setupMainWorkZone();

    QGroupBox* createMainMenu(QWidget *parent);
    QWidget* createAuxMenu(QWidget *parent);
    QGroupBox* createWorkSpace(int conversation_id,QString title,QWidget *parent = nullptr);
    QGroupBox* createNewDialog(QString login, QWidget *parent = nullptr);

    User* takeUserDataFromToken(QString token);

    void handleLogin();
    void handleReg();
    void handleChatButton(int conversation_id, QString title);
    void handleSendMessage(int id_conversation, int message_type_id, QString message);
    void handleLogout();
    void handleUserSearch(QString text);
    void handleOpenDialog(QString user_login);
    void handleCreateConversation(QString user_login, QString message_text);
    void handleDeleteConversation(int conversation_id);
    void handleAddParticipant(int conversation_id);
    void handleChangeConversationName(int conversation_id);
    void handleFriendButton();
    void handleAllFriends();
    void handleDeclineFriends();
    void handleWaitingFriends();
    void handleAddFriend(QString text);
    void handleAcceptFriend(QString login);
    void handleDeclineFriend(QString login);
    void handleCreateGroupe();


public slots:

signals:
    void usersFinded(QStringList);
    void conversationDeleted();
    void participantAdded();
    void restoreData(QStringList);
private:
    RequestBuilder *m_builder = nullptr;
    Ui::MainWindow *ui;
    User *m_user = nullptr;
    PopUp *popup = nullptr;

};
#endif // MAINWINDOW_H
