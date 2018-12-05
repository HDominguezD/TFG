#-------------------------------------------------
#
# Project created by QtCreator 2018-11-13T18:21:31
#
#-------------------------------------------------

include(../../applicationLibraries.pro)

unix:!mac:  APPLICATIONPREFIX = ../..
unix:!mac: EXECUTABLEPATH = $$APPLICATIONPREFIX/ApplicationPackage
unix:!mac: LIBRARIESPATH  = $$APPLICATIONPREFIX/ApplicationPackage
unix:!mac: PLUGINSPATH  = $$APPLICATIONPREFIX/ApplicationPackage/Plugins

DEPENDPATH  *= $$PWD/applicationlib
INCLUDEPATH *= $$PWD/applicationlib

DESTDIR = $$EXECUTABLEPATH

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = application
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

INCLUDEPATH += ../applicationlib

unix:!mac:  LIBS *= -L$$LIBRARIESPATH -lapplicationlib
unix:!mac:  QMAKE_LFLAGS *= -Wl,--rpath=.

SOURCES += main.cpp
