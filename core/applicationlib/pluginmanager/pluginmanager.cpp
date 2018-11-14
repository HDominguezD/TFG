#include "pluginmanager.h"
#include <QDir>
#include <qfiledialog.h>
#include <qexception.h>
#include <qpluginloader.h>
#include "../plugins/plugin.h"
#include "QApplication"


PluginManager::PluginManager()
{
    plugins = new QVector<Plugin*>();
}

void PluginManager::loadPlugins()
{
    // qDebug() << "PluginManager::loadPlugins(..)";

    QDir pluginsDir(getPluginDirPath());
    // without adding the correct library path in the mac the loading of jpg (done via qt plugins) fails
    // qApp->addLibraryPath(getPluginDirPath());
    // qApp->addLibraryPath(getBaseDirPath());

    // qDebug( "Loading plugins from: %s ",qPrintable(pluginsDir.absolutePath()));

    /// Load all plugins
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {

        /// Attempt to load a Qt plugin
        QString path = pluginsDir.absoluteFilePath(fileName);
        QPluginLoader loader(path);
        QObject* _plugin = loader.instance();
        if(!_plugin){
            //qDebug("Plugin '%s' is not a proper *Qt* plugin!! %s", qPrintable(fileName), qPrintable(failurecauses_qtplugin));
            continue;
        }
        loadPlugin(_plugin);
    }
    int hol = 1;
}

bool PluginManager::loadPlugin(QObject* _plugin)
{
    Plugin* plugin = qobject_cast<Plugin*>(_plugin);
    if(!plugin) return false;
    this->plugins->append(plugin);
    return true;
}

QVector<Plugin *> *PluginManager::getPlugins() const
{
    return plugins;
}

QString PluginManager::getPluginDirPath() {
    QDir pluginsDir(qApp->applicationDirPath());
//    if(!pluginsDir.exists("Plugins"))
//        throw QException("Serious error. Unable to find the plugins directory at %s.", qPrintable(pluginsDir.absoluteFilePath("plugins")) );
    pluginsDir.cd("../Plugins");
    return pluginsDir.absolutePath();
}
