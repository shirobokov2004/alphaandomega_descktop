QT       += core gui network uitools websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    apirequestsender.cpp \
    clickablelabel.cpp \
    conversationmenu.cpp \
    downdroplineedit.cpp \
    frienddialog.cpp \
    input.cpp \
    loginform.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    menuitem.cpp \
    message.cpp \
    requestbuilder.cpp \
    popup.cpp \
    websocketconnectionmanager.cpp

HEADERS += \
    apirequestsender.h \
    clickablelabel.h \
    conversationmenu.h \
    downdroplineedit.h \
    frienddialog.h \
    input.h \
    loginform.h \
    mainwindow.h \
    menu.h \
    menuitem.h \
    message.h \
    requestbuilder.h \
    popup.h \
    websocketconnectionmanager.h

FORMS += \
#    login_form.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:RC_ICONS += resources/theme/logo_ANdreya.ico

RESOURCES += \
    resources.qrc
