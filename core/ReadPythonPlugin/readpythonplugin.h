#ifndef READPYTHONPLUGIN_H
#define READPYTHONPLUGIN_H

#include "plugins/executionplugin.h"

class ReadPythonPlugin : public QObject, ExecutionPlugin
{

    Q_OBJECT
    Q_PLUGIN_METADATA(IID "application.plugin/1.0" FILE "readpythonplugin.json")
    Q_INTERFACES(ExecutionPlugin)

public:
    void load();
    const char* getType();
    void close();
    virtual ~ReadPythonPlugin();

};

#endif // READPYTHONPLUGIN_H
