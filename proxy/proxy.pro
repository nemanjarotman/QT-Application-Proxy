QT += core
QT -= gui
QT += network
QT += websockets


CONFIG += c++11

CONFIG += console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

TEMPLATE = app

SOURCES += main.cpp \
    proxy.cpp

HEADERS += \
    proxy.h
