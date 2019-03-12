#-------------------------------------------------
#
# Project created by QtCreator 2018-11-13T18:25:32
#
#-------------------------------------------------

include(../../applicationLibraries.pro)

unix:!mac:  APPLICATIONPREFIX = $$(PWD)/../..
unix:!mac: EXECUTABLEPATH = $$APPLICATIONPREFIX/ApplicationPackage
unix:!mac: LIBRARIESPATH  = $$APPLICATIONPREFIX/ApplicationPackage

DEPENDPATH  *= $$PWD/applicationlib
INCLUDEPATH *= $$PWD/applicationlib
DESTDIR = ../../ApplicationPackage

QT += widgets

TARGET = applicationlib
TEMPLATE = lib

CONFIG += dynamiclib
unix:CONFIG += plugin

# configures rpath
mac:QMAKE_LFLAGS += -install_name @executable_path/lib"$$LIBNAME".dylib
# import / export directive in win32
win32:DEFINES *= DYNAMIC_$$upper($$LIBNAME)

DEFINES += APPLICATIONLIB_LIBRARY

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += /usr/include/python3.6

LIBS += -L/usr/lib/python3.6/config-3.6m-x86_64-linux-gnu/ -lpython3.6
DEPENDPATH += /usr/include/python3.6

SOURCES += \
    renderingwindow.cpp \
    core.cpp \
    objectclasses/objobject.cpp \
    objectclasses/tifobject.cpp \
    objectclasses/tifvolumeobject.cpp \
    pluginmanager/pluginmanager.cpp \
    objectclasses/tifstackobject.cpp \

HEADERS += \
    renderingwindow.h \
    core.h \
    objectclasses/objobject.h \
    objectclasses/tifobject.h \
    objectclasses/objobject.h \
    objectclasses/tifobject.h \
    objectclasses/tifvolumeobject.h \
    objectclasses/abstractclasses/object.h \
    pluginmanager/pluginmanager.h \
    objectclasses/tifstackobject.h \
    plugins/interfaceplugin.h \
    plugins/executionplugin.h

FORMS += \
    renderingwindow.ui

unix {
    target.path = /usr/lib
    INSTALLS += target
}
