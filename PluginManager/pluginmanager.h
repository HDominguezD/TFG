#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H


class PluginManager
{
public:
    PluginManager();
    ~PluginManager();
private:
    void * init();
    void * getToolBar();
    void * close();
    const char * getType();
    void * loadPlugins();
    void* getFunctionPointer(void* lib, const char* funcName);
};

#endif // PLUGINMANAGER_H
