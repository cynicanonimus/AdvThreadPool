#-------------------------------------------------
#
# Project created by QtCreator 2013-04-19T21:55:00
#
#-------------------------------------------------

QT       -= gui

TARGET = AdvThreadPool
TEMPLATE = lib
CONFIG += staticlib

SOURCES += advthreadpool.cpp \
    advthreadjob.cpp \
    advthread.cpp

HEADERS += advthreadpool.h \
    advthreadjob.h \
    advthread.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
