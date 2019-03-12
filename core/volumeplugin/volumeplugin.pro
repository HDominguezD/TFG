#-------------------------------------------------
#
# Project created by QtCreator 2018-11-12T18:07:21
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

TARGET = $$qtLibraryTarget(volumeplugin)
TEMPLATE = lib
CONFIG += plugin

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += ../applicationlib

unix:!mac:  LIBS *= -L$$LIBRARIESPATH -lapplicationlib
unix:!mac:  QMAKE_LFLAGS *= -Wl,--rpath=.

SOURCES += \
        volumeplugin.cpp \
    myqvtkwidget.cpp \
    Editors/transferFunctionEditor.cpp \
    Editors/hoverpoints.cpp \
    Editors/transformeditor.cpp \
    volumewindow.cpp \
    Buttons/camerabutton.cpp \
    Buttons/objectbutton.cpp \
    Pairs/objectpropertiespair.cpp \
    Pairs/camerapropertiespair.cpp

HEADERS += \
        volumeplugin.h \
    myqvtkwidget.h \
    Editors/transferFunctionEditor.h \
    Editors/hoverpoints.h \
    Editors/transformeditor.h \
    volumewindow.h \
    Buttons/camerabutton.h \
    Buttons/objectbutton.h \
    Pairs/objectpropertiespair.h \
    Pairs/camerapropertiespair.h

OTHER_FILES += \
        volumeplugin.json
