#ifndef READPYTHONPLUGIN_H
#define READPYTHONPLUGIN_H

#include "plugins/plugin.h"

class ReadPythonPlugin : public QObject, Plugin
{

    Q_OBJECT
    Q_PLUGIN_METADATA(IID "application.plugin/2.0" FILE "readpythonplugin.json")
    Q_INTERFACES(Plugin)

public:
    void load();
    const char* getType();
    void close();
    virtual ~ReadPythonPlugin();

};

#endif // READPYTHONPLUGIN_H
