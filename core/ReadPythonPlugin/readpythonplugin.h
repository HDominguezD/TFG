#ifndef READPYTHONPLUGIN_H
#define READPYTHONPLUGIN_H

#include "plugins/interfaceplugin.h"
#include "pythonscriptswindow.h"

class ReadPythonPlugin : public QObject, InterfacePlugin
{

    Q_OBJECT
    Q_PLUGIN_METADATA(IID "application.plugin/2.0" FILE "readpythonplugin.json")
    Q_INTERFACES(InterfacePlugin)

public:
    void load();
    const char* getType();
    void close();
    virtual ~ReadPythonPlugin();

private slots:
    void openPythonScript();

private:
    PythonScriptsWindow *window;

};

#endif // READPYTHONPLUGIN_H
