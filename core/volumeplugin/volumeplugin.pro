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
    Editors/transferFunctionEditor.cpp \
    Editors/hoverpoints.cpp \
    volumewindow.cpp \
    Pairs/objectpropertiespair.cpp \
    Pairs/camerapropertiespair.cpp \
    Editors/transformeditorObject.cpp \
    Editors/transformeditorcamera.cpp \
    Editors/objecteditor.cpp \
    TreeWidgetItems/cameratreewidgetitem.cpp \
    TreeWidgetItems/objecttreewidgetitem.cpp \
    Editors/applyconversionseditor.cpp \
    graphicwindow.cpp \
    Editors/Labels/clickablelabel.cpp

HEADERS += \
        volumeplugin.h \
    myqvtkwidget.h \
    Editors/transferFunctionEditor.h \
    Editors/hoverpoints.h \
    volumewindow.h \
    Pairs/objectpropertiespair.h \
    Pairs/camerapropertiespair.h \
    Editors/transformeditorObject.h \
    Editors/transformeditorcamera.h \
    Editors/objecteditor.h \
    TreeWidgetItems/cameratreewidgetitem.h \
    TreeWidgetItems/objecttreewidgetitem.h \
    Editors/applyconversionseditor.h \
    graphicwindow.h \
    Editors/Labels/clickablelabel.h

OTHER_FILES += \
        volumeplugin.json
