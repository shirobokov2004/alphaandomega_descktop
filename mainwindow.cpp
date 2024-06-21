#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QScrollBar"
#include "websocketconnectionmanager.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Messanger");

    //inicialization objects
    m_builder = new RequestBuilder(this);
    m_user = new User();
    popup = new PopUp();

    restoreSettings();

    if(!m_user->getToken().isEmpty()){
        setupMainWorkZone();
        this->setStyleSheet(Style::main);
    }
    else{
        setupLoginWin();
        this->setStyleSheet(Style::login_reg);
    }

    QFont f("Sansation");
    this->setFont(f);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::restoreSettings()
{
    QSettings settings("Settings.ini", QSettings::Format::IniFormat);
    if(settings.contains("user_token")){
        m_user = takeUserDataFromToken(settings.value("user_token").toString());
    }
}

void MainWindow::writeUserToken(QString token)
{
    QSettings settings("Settings.ini", QSettings::Format::IniFormat);
    settings.setValue("user_token", token);
}

void MainWindow::setupRegWin()
{

    QWidget* parent = new QWidget(this);
    parent->setObjectName("parent");

//    delete centralWidget();
    setCentralWidget(parent);

    QVBoxLayout *main_layout = new QVBoxLayout(parent);

    qDebug()<<parent;

    QLabel *l_logo = new QLabel("A&O",parent);
    l_logo->setObjectName("l_logo");
    QGroupBox *gb_loginForm = new QGroupBox(parent);
    gb_loginForm->setContentsMargins(0,0,0,0);

    main_layout->addWidget(l_logo, 0, Qt::AlignHCenter | Qt::AlignTop);
    main_layout->addWidget(gb_loginForm, 1, Qt::AlignHCenter | Qt::AlignVCenter);

    QLabel *l_header = new QLabel("Sign in", gb_loginForm);
    l_header->setObjectName("header");

    ClickableLabel *cl_change = new ClickableLabel(gb_loginForm);
    cl_change->setText("Have no account?");
    cl_change->setObjectName("change");

    QLineEdit *le_login = new QLineEdit(gb_loginForm);
    le_login->setPlaceholderText("login");
    le_login->setObjectName("le_login");;
    le_login->setMinimumWidth(430);

    QLineEdit *le_email = new QLineEdit(gb_loginForm);
    le_email->setPlaceholderText("email");
    le_email->setObjectName("le_email");
    le_email->setMinimumWidth(430);

//    QLineEdit *le_password = new QLineEdit(gb_loginForm);
//    le_password->setPlaceholderText("password");
//    le_password->setObjectName("le_password");
//    le_password->setMinimumWidth(430);
//    le_password->setEchoMode(QLineEdit::Password);
    Input *i_password = new Input(gb_loginForm);
    i_password->setPlaceholderText("password");
    i_password->setObjectName("le_password");
    i_password->setPassword(true);
    i_password->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    i_password->setMinimumWidth(430);

    Input *le_passwordConfirm = new Input(gb_loginForm);
    le_passwordConfirm->setPlaceholderText("repeat password");
    le_passwordConfirm->setObjectName("le_passwordConfirm");
    le_passwordConfirm->setMinimumWidth(430);
    le_passwordConfirm->setPassword(true);

    QPushButton *pb_confirm = new QPushButton("Sign Up",gb_loginForm);
    pb_confirm->setMinimumWidth(430);

    QVBoxLayout *layout = new QVBoxLayout(gb_loginForm);

    layout->addWidget(l_header,1,Qt::AlignCenter);
    layout->addWidget(le_login,1,Qt::AlignCenter);
    layout->addWidget(le_email,1,Qt::AlignCenter);
    layout->addWidget(i_password,1,Qt::AlignCenter);
    layout->addWidget(le_passwordConfirm,1,Qt::AlignCenter);
    layout->addWidget(pb_confirm,1,Qt::AlignCenter);
    layout->addWidget(cl_change,1,Qt::AlignCenter);
    //test
    gb_loginForm->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
//    layout->setStretch(1,10000000);
//    layout->setSpacing(75); отступы от элементов
//    layout->setContentsMargins(10,10,150,10); отступы от элементов

    gb_loginForm->setMinimumSize(530,560);
    gb_loginForm->setMaximumSize(530,560);

    this->setStyleSheet(Style::login_reg);

    connect(pb_confirm, &QPushButton::clicked, this, &MainWindow::handleReg);
    connect(cl_change, &ClickableLabel::clicked, this, &MainWindow::setupLoginWin);
}

void MainWindow::setupLoginWin()
{
    QWidget* parent = new QWidget(this);
    parent->setObjectName("parent");

//    delete centralWidget();
    setCentralWidget(parent);

    QVBoxLayout* main_layout = new QVBoxLayout(parent);

    QLabel *l_logo = new QLabel("A&O",parent);
    l_logo->setObjectName("l_logo");

    qDebug()<<parent;

    QGroupBox *gb_loginForm = new QGroupBox(parent);
    main_layout->addWidget(l_logo, 0, Qt::AlignHCenter | Qt::AlignTop);
    main_layout->addWidget(gb_loginForm, 1, Qt::AlignHCenter | Qt::AlignVCenter);

    QLabel *l_header = new QLabel("Log in", gb_loginForm);
    l_header->setObjectName("header");

    ClickableLabel *cl_change = new ClickableLabel(gb_loginForm);
    cl_change->setText("Already have account?");
    cl_change->setObjectName("change");

    QLineEdit *le_login = new QLineEdit(gb_loginForm);
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

    this->setStyleSheet(Style::login_reg);

    connect(pb_confirm, &QPushButton::clicked, this, &MainWindow::handleLogin);
    connect(cl_change, &ClickableLabel::clicked, this, &MainWindow::setupRegWin);
}

void MainWindow::setupMainWorkZone()
{

    QWidget* parent = new QWidget(this);
    parent->setObjectName("parent");

//    centralWidget()->deleteLater();
    setCentralWidget(parent);

    QHBoxLayout* main_layout = new QHBoxLayout(parent);

    main_layout->setContentsMargins(0,0,0,0);
    main_layout->setSpacing(0);

    //Container init
    QGroupBox *gb_mainMenu = createMainMenu(parent);
    gb_mainMenu->setObjectName("mainMenu");

    QWidget *sa_auxMenu = createAuxMenu(parent);
    sa_auxMenu->setObjectName("auxMenu");

    QGroupBox *gb_workSpace = new QGroupBox(parent);
    gb_workSpace->setObjectName("workSpace");

    main_layout->addWidget(gb_mainMenu);
    main_layout->addWidget(sa_auxMenu);
    main_layout->addWidget(gb_workSpace);
    this->setStyleSheet(Style::main);
}

QGroupBox* MainWindow::createMainMenu(QWidget *parent)
{
    QGroupBox *gb_mainMenu = new QGroupBox(parent);
    gb_mainMenu->setObjectName("gb_mainMenu");
    gb_mainMenu->setMinimumWidth(100);
    gb_mainMenu->setMaximumWidth(100);

    QVBoxLayout *layout_mainMenu = new QVBoxLayout(gb_mainMenu);
    layout_mainMenu->setContentsMargins(0,0,0,0);
    layout_mainMenu->setSpacing(0);

    QLabel *l_logo = new QLabel("A&O", gb_mainMenu);
    l_logo->setMaximumSize(80,50);
    l_logo->setMinimumSize(80,50);

    QPushButton *pb_setting = new QPushButton("setting",gb_mainMenu);
    QPushButton *pb_messenger = new QPushButton("messenger",gb_mainMenu);
    QPushButton *pb_friends = new QPushButton("friends",gb_mainMenu);
    QPushButton *pb_logout = new QPushButton("logout",gb_mainMenu);
    connect(pb_logout, &QPushButton::clicked, this, handleLogout);
    connect(pb_friends, &QPushButton::clicked, this, &MainWindow::handleFriendButton);

    layout_mainMenu->addWidget(l_logo,0,Qt::AlignTop);
    layout_mainMenu->addWidget(pb_setting);
    layout_mainMenu->addWidget(pb_messenger);
    layout_mainMenu->addWidget(pb_friends);
    layout_mainMenu->addWidget(pb_logout,1,Qt::AlignBottom);
    return gb_mainMenu;
}

QWidget* MainWindow::createAuxMenu(QWidget *parent)
{
    QWidget *sa_auxMenu = new QWidget(parent);
    sa_auxMenu->setMinimumWidth(432);
    sa_auxMenu->setMaximumWidth(432);

    QVBoxLayout *sa_lay = new QVBoxLayout(sa_auxMenu);

    DownDropLineEdit *ddle_search = new DownDropLineEdit();

    QPushButton *pb_createConversation = new QPushButton("Create new conversation", this);
    pb_createConversation->setObjectName("pb_createConversation");
    pb_createConversation->setMaximumHeight(70);

    QScrollArea *qwerty = new QScrollArea();

    QWidget *qweqwe = new QWidget(qwerty);

    QVBoxLayout *layout_auxMenu = new QVBoxLayout(qweqwe);

    QJsonArray menuItems = m_builder->getConversations(m_user->getToken(), m_user->getId());
    for(int i = 0;i<menuItems.count();i++){
        QVariantMap vars = menuItems.at(i).toObject().toVariantMap();
        QString title = vars.value("title").toString();
        if(vars.value("type").toString() == "dialogue"){
            if(title.indexOf(m_user->getLogin())>0){
                title = title.chopped(m_user->getLogin().size() + 1);
            }
            else{
                title.remove(0, m_user->getLogin().size() + 1);
            }
        }
        MenuItem *w_menuItem = new MenuItem(title ,vars.value("conversation_id").toInt(),qwerty);
        w_menuItem->setMaximumSize(sa_auxMenu->width(), 40);
        w_menuItem->setMinimumSize(sa_auxMenu->width(), 40);
        layout_auxMenu->addWidget(w_menuItem);
        connect(w_menuItem, &MenuItem::clicked, this, &MainWindow::handleChatButton);
    }

    sa_lay->addWidget(ddle_search);
    sa_lay->addWidget(qwerty);
    sa_lay->addWidget(pb_createConversation);

    sa_lay->setContentsMargins(0,0,0,0);
    sa_lay->setSpacing(0);
    layout_auxMenu->setContentsMargins(0,0,0,0);
    layout_auxMenu->setSpacing(0);



    qweqwe->setObjectName("itemWrapper");
//    qweqwe->setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred));
    ddle_search->setPlaceholderText("Search");
//    ddle_search->setMaximumSize(400, 35);
//    ddle_search->setMinimumSize(400, 35);


    qwerty->setWidget(qweqwe);

    qwerty->setStyleSheet("border: 0px;");
//    qwerty->setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred));
//    qwerty->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    qwerty->verticalScrollBar()->hide();

    connect(ddle_search, &DownDropLineEdit::userSearch, this, &MainWindow::handleUserSearch);
    connect(this, &MainWindow::usersFinded, ddle_search, &DownDropLineEdit::updateCompleter);
    connect(ddle_search, &DownDropLineEdit::userSelected, this, &MainWindow::handleOpenDialog);
    connect(pb_createConversation, &QPushButton::clicked, this, &MainWindow::handleCreateGroupe);
    return sa_auxMenu;
}

QGroupBox* MainWindow::createWorkSpace(int conversation_id, QString title, QWidget *parent)
{
    QGroupBox *gb_workSpace = new QGroupBox(parent);

    QVBoxLayout *layout_workSpace = new QVBoxLayout(gb_workSpace);
    layout_workSpace->setContentsMargins(0,0,0,0);
    layout_workSpace->setSpacing(0);

    QWidget *w_header = new QWidget(gb_workSpace);
    w_header->setObjectName("header");
    QGridLayout *layout_header = new QGridLayout(w_header);

    QLabel *l_personName = new QLabel(title, w_header);
    l_personName->setObjectName("title");
    QLabel *l_lastSeenTime = new QLabel("last seen recently", w_header);
    layout_header->addWidget(l_personName,1,1);
    layout_header->addWidget(l_lastSeenTime,2,1);

    ConversationMenu *cb = new ConversationMenu(this);
    layout_header->addWidget(cb,1,2,2,1);
    connect(cb, &ConversationMenu::currentTextChanged, [=](QString text){
        if(text == "Delete conversation"){
            handleDeleteConversation(conversation_id);
        }
        if(text == "Add participant"){
            handleAddParticipant(conversation_id);
        }
        if(text == "Change name"){
            handleChangeConversationName(conversation_id);
        }
        cb->setCurrentIndex(0);
    });

    QScrollArea *sa_messageArea = new QScrollArea(gb_workSpace);
    sa_messageArea->setWidgetResizable(true);
    sa_messageArea->verticalScrollBar()->hide();

    QWidget *w_messageStore = new QWidget(sa_messageArea);
    w_messageStore->setObjectName("messageStore");
    QVBoxLayout *layout_messageStore = new QVBoxLayout(w_messageStore);
    layout_messageStore->addSpacing(1000);

    QJsonArray mess = m_builder->getMessage(conversation_id, m_user->getToken());
    for(int i = 0;i<mess.count();i++){
        QVariantMap message = mess.at(i).toObject().toVariantMap();
        Message *m_mess = new Message(message.value("user").toMap().value("login").toString(),message.value("messages").toString(), message.value("created_at").toString(), w_messageStore);//createMessage(message.value("messages").toString(), w_messageStore);
        m_mess->setGuid(message.value("guid").toString());
        if(message.value("sender_id").toInt() == m_user->getId()){
            layout_messageStore->addWidget(m_mess,0,Qt::AlignRight | Qt::AlignBottom);
        }
        else{
            layout_messageStore->addWidget(m_mess,0,Qt::AlignLeft | Qt::AlignBottom);
        }
        connect(m_mess, &Message::deleteMessage, [=](QString guid){m_builder->deleteMessage(m_user->getToken(), guid).toVariantMap();});
        connect(m_mess, &Message::changeMessage, [=](QString guid, QString text){m_builder->updateMessage(m_user->getToken(), guid, text);});
    }
    sa_messageArea->setWidget(w_messageStore);
    QScrollBar *scr =  sa_messageArea->verticalScrollBar();
    scr->setValue(scr->maximum());

    QLineEdit *le_input = new QLineEdit(gb_workSpace);
    le_input->setObjectName("messageInput");
    le_input->setPlaceholderText("Send message");
    connect(le_input, &QLineEdit::returnPressed, [=](){handleSendMessage(conversation_id, 1,le_input->text()); le_input->clear();} );

    layout_workSpace->addWidget(w_header);
    layout_workSpace->addWidget(sa_messageArea);
    layout_workSpace->addWidget(le_input);
    return gb_workSpace;
}

QGroupBox *MainWindow::createNewDialog(QString login, QWidget *parent)
{
    QGroupBox *gb_workSpace = new QGroupBox(parent);

    QVBoxLayout *layout_workSpace = new QVBoxLayout(gb_workSpace);
    layout_workSpace->setContentsMargins(0,0,0,0);
    layout_workSpace->setSpacing(0);

    QWidget *w_header = new QWidget(gb_workSpace);
    w_header->setObjectName("header");
    QGridLayout *layout_header = new QGridLayout(w_header);

    QLabel *l_personName = new QLabel(login, w_header);
    l_personName->setObjectName("title");
    QLabel *l_lastSeenTime = new QLabel("last seen recently", w_header);
    layout_header->addWidget(l_personName,1,1);
    layout_header->addWidget(l_lastSeenTime,2,1);


    QScrollArea *sa_messageArea = new QScrollArea(gb_workSpace);
    sa_messageArea->setWidgetResizable(true);

    QWidget *w_messageStore = new QWidget(sa_messageArea);
    w_messageStore->setObjectName("messageStore");
    QVBoxLayout *layout_messageStore = new QVBoxLayout(w_messageStore);

    sa_messageArea->setWidget(w_messageStore);
    QScrollBar *scr =  sa_messageArea->verticalScrollBar();
    scr->setValue(scr->maximum());

    QLineEdit *le_input = new QLineEdit(gb_workSpace);
    le_input->setObjectName("messageInput");
    le_input->setPlaceholderText("Send message");
    connect(le_input, &QLineEdit::returnPressed, [=](){handleCreateConversation(login, le_input->text());});

    layout_workSpace->addWidget(w_header);
    layout_workSpace->addWidget(sa_messageArea);
    layout_workSpace->addWidget(le_input);
    return gb_workSpace;
}

MainWindow::User* MainWindow::takeUserDataFromToken(QString token)
{
    qDebug()<<token;
    QVariantMap userData = m_builder->getUser(token).toVariantMap();
    User* user = new User();
    if(userData.value("message").toString() == "Unauthenticated"){
        qDebug()<<"token restored";
        return user;
    }
    user->setId(userData.value("id").toInt());
    user->setLogin(userData.value("login").toString());
    user->setPhone(userData.value("phone").toInt());
    user->setEmail(userData.value("email").toString());
    user->setFirstName(userData.value("first_name").toString());
    user->setLastName(userData.value("last_name").toString());
    user->setMiddleName(userData.value("middle_name").toString());
    user->setAvatar(userData.value("avatar").toString());
    user->setIsActive(userData.value("is_active").toBool());
    user->setIsBlocked(userData.value("is_blocked").toBool());
    user->setStatusId(userData.value("status_id").toInt());
    user->setToken(token);

    return user;
}

void MainWindow::handleLogin()
{
    QPushButton *btn = dynamic_cast<QPushButton*>(sender());
    btn->setDisabled(true);
    QString login = centralWidget()->findChild<QLineEdit*>("le_login")->text();
    QString password = centralWidget()->findChild<QLineEdit*>("le_password")->text();
    QVariantMap res = m_builder->postLogin(login, password).toVariantMap();
    qDebug()<<"login responce " << res;
    QString token = res.value("access_token").toString();
    if(!token.isEmpty()){
        m_user = takeUserDataFromToken(token);
        writeUserToken(m_user->getToken());
        setupMainWorkZone();
    }
    else
        btn->setDisabled(false);
}

void MainWindow::handleReg()
{
    QString login = centralWidget()->findChild<QLineEdit*>("le_login")->text();
    QString password = centralWidget()->findChild<QLineEdit*>("le_password")->text();
    QString password_confirmation = centralWidget()->findChild<QLineEdit*>("le_passwordConfirm")->text();
    QString email = centralWidget()->findChild<QLineEdit*>("le_email")->text();
    QVariantMap res = m_builder->postRegister(login,password,password_confirmation,email).toVariantMap();
    qDebug()<<"reg responce " << res;

    QString token = res.value("access_token").toString();
    if(!token.isEmpty()){
        m_user = takeUserDataFromToken(token);
        writeUserToken(m_user->getToken());
        setupMainWorkZone();
    }
}

void MainWindow::handleChatButton(int conversation_id, QString title)
{
    QGroupBox *workSpace = this->findChild<QGroupBox*>("workSpace");
    workSpace->deleteLater();
    QGroupBox *new_workSpace = createWorkSpace(conversation_id, title, centralWidget());
    new_workSpace->setObjectName("workSpace");
    centralWidget()->layout()->addWidget(new_workSpace);
    this->setStyleSheet(Style::main);
}

void MainWindow::handleSendMessage(int id_conversation, int message_type_id, QString text)
{
    if(text.isEmpty())
        return;
    QJsonObject mess = m_builder->postSendMessage(m_user->getToken() , id_conversation, m_user->getId(), message_type_id, text);
    QWidget* messStore = centralWidget()->findChild<QWidget*>("messageStore");
    QVBoxLayout* lay = (QVBoxLayout*)messStore->layout();
    QVariantMap message = mess.toVariantMap();
    Message *m_mess = new Message(m_user->getLogin() ,message.value("messages").toString(), message.value("created_at").toString(), messStore);//createMessage(message.value("messages").toString(), w_messageStore);
    m_mess->setGuid(message.value("guid").toString());
    if(message.value("sender_id").toInt() == m_user->getId()){
        lay->addWidget(m_mess,1,Qt::AlignRight | Qt::AlignBottom);
    }
    else{
        lay->addWidget(m_mess,1,Qt::AlignLeft | Qt::AlignBottom);
    }
}

void MainWindow::handleLogout()
{
    QSettings settings("Settings.ini", QSettings::Format::IniFormat);
    settings.clear();
    m_user = new User();
    setupLoginWin();
}

void MainWindow::handleUserSearch(QString text)
{
    if(text.length()<3){
        emit usersFinded(QStringList());
        return;
    }
    QJsonObject obj = m_builder->postSearchUsers(text, m_user->getToken());
    QVariantMap data = obj.toVariantMap();
    QStringList userNames;
    for(int i = 0; i < data.value("data").toList().count(); i++){
        userNames.append(data.value("data").toList().at(i).toMap().value("login").toString());
    }
    emit usersFinded(userNames);
}

void MainWindow::handleOpenDialog(QString user_login)
{
    qDebug()<<"handle open dialog";
    QGroupBox *workSpace = this->findChild<QGroupBox*>("workSpace");
    workSpace->deleteLater();
    QGroupBox *new_workSpace = createNewDialog(user_login, centralWidget());
    new_workSpace->setObjectName("workSpace");
    centralWidget()->layout()->addWidget(new_workSpace);
    this->setStyleSheet(Style::main);
}

void MainWindow::handleCreateConversation(QString user_login, QString message_text)
{
    QString chanel_id = QUuid::createUuid().toString();
    qDebug()<<chanel_id;
//    создание диалога
    QJsonObject conversation = m_builder->postCreateConversation(m_user->getToken(), user_login + "_" + m_user->getLogin(), chanel_id, m_user->getId(), "dialogue");
//    поиск юзера по id
    QJsonObject users = m_builder->postSearchUsers(user_login, m_user->getToken());
    int user_id = users.toVariantMap().value("data").toList().at(0).toMap().value("id").toInt();
//    добавлние участника
    qDebug()<<m_user->getToken()<<conversation.toVariantMap().value("conversation").toMap().value("id").toInt()<<user_id;
    QJsonObject participant = m_builder->postAddParticipant(m_user->getToken(), conversation.toVariantMap().value("conversation").toMap().value("id").toInt(), user_id, 2);
//    отправка сообщения
    QJsonObject message = m_builder->postSendMessage(m_user->getToken(), conversation.toVariantMap().value("conversation").toMap().value("id").toInt(), m_user->getId(), 1, message_text);
//    перерисовка ui
//обновление aux menu
//    QScrollArea *aux_menu = ui->centralwidget->findChild<QScrollArea*>("auxMenu");
//    clearWidget(aux_menu);
//    createAuxMenu(ui->centralwidget->findChild<QWidget*>("parent"));
    setupMainWorkZone();
    //обновление work zone
}

void MainWindow::handleDeleteConversation(int conversation_id)
{
    emit conversationDeleted();
    qDebug()<<m_builder->deleteConversation(m_user->getToken(), conversation_id).toVariantMap();
    setupMainWorkZone();
}

void MainWindow::handleAddParticipant(int conversation_id)
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Add participant"),
                                             tr("Login participant"), QLineEdit::Normal,
                                             "" ,&ok);
    if(ok && !text.isEmpty()){
        emit participantAdded();
        QJsonObject users = m_builder->postSearchUsers(text, m_user->getToken());
        int user_id = users.toVariantMap().value("data").toList().at(0).toMap().value("id").toInt();
        qDebug()<<text<<QString::number(user_id);
        m_builder->addParticipant(m_user->getToken(), conversation_id, user_id, 2);
    }
}

void MainWindow::handleChangeConversationName(int conversation_id)
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Add participant"),
                                             tr("Login participant"), QLineEdit::Normal,
                                             "" ,&ok);
    if(ok && !text.isEmpty()){
        qDebug()<<text;
        m_builder->updateConversationName(m_user->getToken(), conversation_id, text);
        setupMainWorkZone();
    }
}

void MainWindow::handleFriendButton()
{
    FriendDialog *dialog = new FriendDialog(this);
    connect(this, &MainWindow::restoreData, dialog, &FriendDialog::newData);
    connect(dialog, &FriendDialog::allButtonActivated, this, &MainWindow::handleAllFriends);
    connect(dialog, &FriendDialog::declineButtonActivated, this, &MainWindow::handleDeclineFriends);
    connect(dialog, &FriendDialog::waitingButtonActivated, this, &MainWindow::handleWaitingFriends);
    connect(dialog, &FriendDialog::addFriendButtonActivated, this, &MainWindow::handleAddFriend);
    connect(dialog, &FriendDialog::acceptFriendActivated, this, &MainWindow::handleAcceptFriend);
    connect(dialog, &FriendDialog::declineFriendActivated, this, &MainWindow::handleDeclineFriend);
    dialog->exec();
}

void MainWindow::handleAllFriends()
{
    QJsonArray users = m_builder->getFriends(m_user->getToken());
    QStringList list;
    QVariantList users_list = users.toVariantList();
    for(int i = 0; i < users_list.count(); i++){
        list.append(users_list.value(i).toMap().value("first_friend").toMap().value("login").toString());
    }
    emit restoreData(list);
}

void MainWindow::handleDeclineFriends()
{
    QJsonArray users = m_builder->getDeclinedFriends(m_user->getToken());
    QStringList list;
    QVariantList users_list = users.toVariantList();
    for(int i = 0; i < users_list.count(); i++){
        list.append(users_list.value(i).toMap().value("first_friend").toMap().value("login").toString());
    }
    emit restoreData(list);
}

void MainWindow::handleWaitingFriends()
{
    QJsonArray users = m_builder->getWaitingFriends(m_user->getToken());
    QStringList list;
    QVariantList users_list = users.toVariantList();
    for(int i = 0; i < users_list.count(); i++){
        list.append(users_list.value(i).toMap().value("first_friend").toMap().value("login").toString());
    }
    emit restoreData(list);
}

void MainWindow::handleAddFriend(QString text)
{
    QJsonObject users = m_builder->postSearchUsers(text, m_user->getToken());
    int user_id = users.toVariantMap().value("data").toList().at(0).toMap().value("id").toInt();
    if(user_id>0){
        m_builder->postAddFriend(m_user->getToken(), text);
    }
}

void MainWindow::handleAcceptFriend(QString login)
{
    m_builder->updateStatus(m_user->getToken(), "accepted", login);
    handleAllFriends();
}

void MainWindow::handleDeclineFriend(QString login)
{
    m_builder->updateStatus(m_user->getToken(), "decline", login);
    handleAllFriends();
}

void MainWindow::handleCreateGroupe()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Create conversation"),
                                             tr("Conversation title"), QLineEdit::Normal,
                                             "" ,&ok);
    if(ok && !text.isEmpty()){
        m_builder->postCreateConversation(m_user->getToken(), text, QUuid::createUuid().toString(), m_user->getId(), "group");
        setupMainWorkZone();
    }
}
