QT += opengl xml
TEMPLATE = lib
CONFIG += plugin
DESTDIR = $$PLUGINSPATH
DEPENDPATH *= $$PWD

SOURCES += \
    renderingwindow.cpp \
    core.cpp \
    main.cpp \
    ObjectClasses/objobject.cpp \
    ObjectClasses/tifobject.cpp \
    ObjectClasses/tifvolumeobject.cpp \
    PluginManager/pluginmanager.cpp \
    Plugins/dinamiclibraryexample.cpp \
    Plugins/surfaceplugin.cpp \
    PluginManager/pluginmanager2.cpp \

HEADERS += \
    renderingwindow.h \
    core.h \
    ObjectClasses/objobject.h \
    ObjectClasses/tifobject.h \
    ObjectClasses/objobject.h \
    ObjectClasses/tifobject.h \
    ObjectClasses/tifvolumeobject.h \
    PluginManager/pluginmanager.h \
    Plugins/dinamiclibraryexample.h \
    Plugins/plugin.h \
    Plugins/surfaceplugin.h \
    ObjectClasses/AbstractClasses/object.h \
    PluginManager/pluginmanager2.h \

