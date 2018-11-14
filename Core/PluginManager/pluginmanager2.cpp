#include "pluginmanager2.h"
#include <QDir>
#include <qfiledialog.h>
#include <qexception.h>
#include <qpluginloader.h>
#include "../Plugins/plugin.h"


PluginManager2::PluginManager2()
{
    plugins = new QVector<Plugin*>();
}

void PluginManager2::loadPlugins()
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

bool PluginManager2::loadPlugin(QObject* _plugin)
{
    Plugin* plugin = qobject_cast<Plugin*>(_plugin);
    if(!plugin) return false;
    this->plugins->append(plugin);
    return true;
}

QVector<Plugin *> *PluginManager2::getPlugins() const
{
    return plugins;
}

QString PluginManager2::getPluginDirPath() {
    QDir pluginsDir = QFileDialog::getExistingDirectory(0, QObject::tr("select directory"));
//    if(!pluginsDir.exists("plugins"))
//        throw QException("Serious error. Unable to find the plugins directory at %s.", qPrintable(pluginsDir.absoluteFilePath("plugins")) );
    pluginsDir.cd("plugins");
    return pluginsDir.absolutePath();
}
