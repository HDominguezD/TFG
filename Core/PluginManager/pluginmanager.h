#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "QMenu";
#include "qmenubar.h"


class PluginManager
{
public:
    PluginManager();
    QMenu * init(QMenuBar* bar);
    ~PluginManager();
private:
    void * getToolBar();
    void * close();
    const char * getType();
    void * loadPlugins();
    void* getFunctionPointer(void* lib, const char* funcName);
};

#endif // PLUGINMANAGER_H
