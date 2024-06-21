#ifndef FRIENDDIALOG_H
#define FRIENDDIALOG_H

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QListView>
#include <QStringListModel>
#include <QInputDialog>
#include <QMenu>

class FriendDialog : public QDialog
{
    Q_OBJECT
public:
    FriendDialog(QWidget *parent = nullptr);

    void allButton();
    void declineButton();
    void waitingButton();
    void addFriendButton();
    void acceptFriend();
    void declineFriend();

    void newData(QStringList list);

signals:
    void allButtonActivated();
    void declineButtonActivated();
    void waitingButtonActivated();
    void addFriendButtonActivated(QString);
    void acceptFriendActivated(QString);
    void declineFriendActivated(QString);
private:
    void handleContextMenuRequested(QPoint pos);
    QStringListModel *model = nullptr;
    QMenu *menu = nullptr;
    QListView *list = nullptr;
};

#endif // FRIENDDIALOG_H
