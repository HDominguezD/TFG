#ifndef PLUGINMANAGER2_H
#define PLUGINMANAGER2_H

#include <QString>
#include "QObject"
#include "../plugins/plugin.h"


class PluginManager
{
public:
    PluginManager();
    void loadPlugins();

    QVector<Plugin *> *getPlugins() const;

private:
    QString getPluginDirPath();
    bool loadPlugin(QObject* _plugin);

    QVector<Plugin*>* plugins;
};

#endif // PLUGINMANAGER2_H
