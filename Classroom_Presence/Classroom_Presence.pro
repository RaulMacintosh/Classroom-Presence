#-------------------------------------------------
#
# Project created by QtCreator 2016-06-03T14:54:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Classroom_Presence
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    creationwindow.cpp

HEADERS  += mainwindow.h \
    creationwindow.h

FORMS    += mainwindow.ui \
    creationwindow.ui

CONFIG  += c++11
QMAKE_CXXFLAGS += -std=c++11 -stdlib=libc++
LIBS += -pthread

DISTFILES +=
