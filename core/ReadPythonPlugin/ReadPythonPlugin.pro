#-------------------------------------------------
#
# Project created by QtCreator 2019-02-18T10:54:25
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

TARGET = $$qtLibraryTarget(readpythonplugin)
TEMPLATE = lib
CONFIG += plugin

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += ../applicationlib
INCLUDEPATH += /usr/include/python3.6

LIBS += -L/usr/lib/python3.6/config-3.6m-x86_64-linux-gnu/ -lpython3.6
DEPENDPATH += /usr/include/python3.6

unix:!mac:  LIBS *= -L$$LIBRARIESPATH -lapplicationlib
unix:!mac:  QMAKE_LFLAGS *= -Wl,--rpath=.

HEADERS += \
    readpythonplugin.h \
    pythonscriptswindow.h

SOURCES += \
    readpythonplugin.cpp \
    pythonscriptswindow.cpp

OTHER_FILES    += readpythonplugin.json

FORMS += \
    pythonscriptswindow.ui
