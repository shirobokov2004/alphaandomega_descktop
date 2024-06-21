#include "frienddialog.h"

FriendDialog::FriendDialog(QWidget *parent)
    :QDialog(parent)
{
    QGridLayout *layout = new QGridLayout(this);

    QPushButton *all = new QPushButton("All" ,this);
    QPushButton *waiting = new QPushButton("Waiting" ,this);
    QPushButton *decline = new QPushButton("Decline", this);
    QPushButton *addFriend = new QPushButton("Add friend", this);
    list = new QListView(this);
    list->setContextMenuPolicy(Qt::CustomContextMenu);
    menu = new QMenu(this);
    QAction *action_accept = new QAction("Accept", this);
    QAction *decline_accept = new QAction("Decline", this);
    menu->addAction(action_accept);
    menu->addAction(decline_accept);

    model = new QStringListModel(this);
    list->setModel(model);

    layout->addWidget(all ,1,1);
    layout->addWidget(waiting ,1,2);
    layout->addWidget(decline ,1,3);
    layout->addWidget(addFriend ,1,4);
    layout->addWidget(list, 2,1,1,4);

    connect(all, &QPushButton::clicked, this, &FriendDialog::allButton);
    connect(waiting, &QPushButton::clicked, this, &FriendDialog::waitingButton);
    connect(decline, &QPushButton::clicked, this, &FriendDialog::declineButton);
    connect(addFriend, &QPushButton::clicked, this, &FriendDialog::addFriendButton);
    connect(list, &QListView::customContextMenuRequested, this, &FriendDialog::handleContextMenuRequested);
    connect(action_accept, &QAction::triggered, this, &FriendDialog::acceptFriend);
    connect(decline_accept, &QAction::triggered, this, &FriendDialog::declineFriend);
}

void FriendDialog::allButton()
{
    emit allButtonActivated();
}

void FriendDialog::declineButton()
{
    emit declineButtonActivated();
}

void FriendDialog::waitingButton()
{
    emit waitingButtonActivated();
}

void FriendDialog::addFriendButton()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Add friend"),
                                         tr("User login:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()){
        qDebug()<<text;
        emit addFriendButtonActivated(text);
    }
}

void FriendDialog::acceptFriend()
{
    QModelIndex index = list->currentIndex();
    QString login = model->data(index).toString();
    emit acceptFriendActivated(login);
}

void FriendDialog::declineFriend()
{
    QModelIndex index = list->currentIndex();
    QString login = model->data(index).toString();
    emit declineFriendActivated(login);
}

void FriendDialog::newData(QStringList list)
{
    model->setStringList(list);
}

void FriendDialog::handleContextMenuRequested(QPoint pos)
{
    menu->popup(this->mapToGlobal(pos));
}

