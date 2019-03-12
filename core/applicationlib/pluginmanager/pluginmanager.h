#ifndef PLUGINMANAGER2_H
#define PLUGINMANAGER2_H

#include "QObject"
#include "../plugins/interfaceplugin.h"
#include "../plugins/executionplugin.h"


class PluginManager
{
public:
    PluginManager();
    void loadPlugins();

    QVector<ExecutionPlugin *> *getExecutionPlugins() const;

    QVector<InterfacePlugin *> *getInterfacePlugins() const;

private:
    QString getPluginDirPath();
    bool loadPlugin(QObject *_plugin);
    QVector<InterfacePlugin*>* interfacePlugins;
    QVector<ExecutionPlugin*>* executionPlugins;
};

#endif // PLUGINMANAGER2_H
