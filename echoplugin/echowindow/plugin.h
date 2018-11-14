#ifndef PLUGIN_H
#define PLUGIN_H

#include "QtPlugin"

class Plugin
{

public:

    virtual void load() = 0;
    virtual const char * getType() = 0;
    virtual void close() = 0;
    int *hola;
    int *getHola() const{ return hola;}
    void setHola(int *value){hola = value;}
};

#define PluginInterface_iid "application::Plugin/2.0"

Q_DECLARE_INTERFACE(Plugin, PluginInterface_iid)

#endif // PLUGIN_H
