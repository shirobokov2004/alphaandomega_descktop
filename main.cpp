#include "mainwindow.h"
#include "apirequestsender.h"
#include "requestbuilder.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    RequestBuilder builder;
//    QJsonObject obj = builder.postSendMessage(1,1,1,"Привет 2!!!");
//    qDebug()<<obj;

    return a.exec();
}
