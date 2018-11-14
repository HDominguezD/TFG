#include "pluginmanager.h"
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <QMenu>
#include <QDebug>
#include <qwidget.h>
#include <QApplication>
#include <qmenubar.h>

PluginManager::PluginManager()
{
}

QMenu * PluginManager::init(QMenuBar* bar)
{
    void *handle;
    QMenu* (*menu)(QMenuBar*);
    char *error;

    handle = dlopen ("Plugins/surfacePlugin.so", RTLD_NOW);
    if (!handle) {
        fputs (dlerror(), stderr);
        exit(1);
    }

    *(void **) (&menu) = dlsym(handle, "getMenu");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        exit(1);
    }

    QMenu* value = (*menu)(bar);
    dlclose(handle);
    loadPlugins();

    return value;
}

void * PluginManager::loadPlugins()
{

}

void * PluginManager::getToolBar()
{

}
void * PluginManager::close()
{

}
const char * PluginManager::getType()
{

}
