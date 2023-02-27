#-------------------------------------------------
#
# Project created by QtCreator 2023-01-17T20:01:24
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TcpClient
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        tcpclient.cpp \
    protocol.cpp \
    opewidget.cpp \
    online.cpp \
    friend.cpp \
    book.cpp \
    privatechat.cpp \
    sharefile.cpp

HEADERS += \
        tcpclient.h \
    protocol.h \
    opewidget.h \
    online.h \
    friend.h \
    book.h \
    privatechat.h \
    sharefile.h

FORMS += \
        tcpclient.ui \
    online.ui \
    privatechat.ui

RESOURCES += \
    config.qrc \
    filetype.qrc
