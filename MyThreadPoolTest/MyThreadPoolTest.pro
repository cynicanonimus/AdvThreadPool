#-------------------------------------------------
#
# Project created by QtCreator 2013-04-18T15:55:24
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = MyThreadPoolTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    jobfortests.cpp

HEADERS += \
    jobfortests.h

unix:!macx:!symbian|win32: LIBS += -L$$PWD/../AdvThreadPool/ -lAdvThreadPool

INCLUDEPATH += $$PWD/../AdvThreadPool
DEPENDPATH += $$PWD/../AdvThreadPool

win32: PRE_TARGETDEPS += $$PWD/../AdvThreadPool/AdvThreadPool.lib
else:unix:!macx:!symbian: PRE_TARGETDEPS += $$PWD/../AdvThreadPool/libAdvThreadPool.a
