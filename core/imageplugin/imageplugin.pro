#-------------------------------------------------
#
# Project created by QtCreator 2018-11-16T10:35:49
#
#-------------------------------------------------

include(../../applicationLibraries.pro)

unix:!mac: APPLICATIONPREFIX = ../..
unix:!mac: EXECUTABLEPATH = $$APPLICATIONPREFIX/ApplicationPackage
unix:!mac: LIBRARIESPATH  = $$APPLICATIONPREFIX/ApplicationPackage
unix:!mac: PLUGINSPATH  = $$APPLICATIONPREFIX/ApplicationPackage/Plugins
unix:!mac: EXECUTABLEPATH = $$APPLICATIONPREFIX/ApplicationPackage

DESTDIR = $$PLUGINSPATH

QT*=xml opengl widgets

TARGET = $$qtLibraryTarget(imageplugin)
TEMPLATE = lib
CONFIG += plugin

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += ../applicationlib

unix:!mac:  LIBS *= -L$$LIBRARIESPATH -lapplicationlib
unix:!mac:  QMAKE_LFLAGS *= -Wl,--rpath=.

SOURCES += \
        imageplugin.cpp

HEADERS += \
        imageplugin.h

OTHER_FILES += \
        imageplugin.json
