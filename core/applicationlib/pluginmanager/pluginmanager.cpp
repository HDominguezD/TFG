#include "pluginmanager.h"
#include <QDir>
#include <qfiledialog.h>
#include <qexception.h>
#include <qpluginloader.h>
#include "QApplication"
#include "QException"
#include "QDebug"


PluginManager::PluginManager()
{
    executionPlugins = new QVector<ExecutionPlugin*>();
    interfacePlugins = new QVector<InterfacePlugin*>();
}

void PluginManager::loadPlugins()
{
    qDebug() << "PluginManager::loadPlugins(..)";

    QDir pluginsDir(getPluginDirPath());

    qDebug( "Loading plugins from: %s ",qPrintable(pluginsDir.absolutePath()));

    QString failurecauses_qtplugin(
    "\nPOSSIBLE FAILURE REASONS:\n"
    "  1) plugin needs a DLL which cannot be found in the executable folder\n"
    "  2) Release / debug build mismatch\n"
    "  3) Missing Q_INTERFACE(...) or Q_EXPORT_PLUGIN(...)\n"
    "  *) any other reason?");

    /// Load all plugins
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {

        /// Attempt to load a Qt plugin
        QString path = pluginsDir.absoluteFilePath(fileName);
        QPluginLoader loader(path);
        QObject* _plugin = loader.instance();
        if(!_plugin){
            QString error = loader.errorString();
            qDebug() << error;
            qDebug("Plugin '%s' is not a proper *Qt* plugin!! %s", qPrintable(fileName), qPrintable(failurecauses_qtplugin));
            continue;
        }
        loadPlugin(_plugin);
    }
}

bool PluginManager::loadPlugin(QObject* _plugin)
{
    InterfacePlugin* interfacePlugin = qobject_cast<InterfacePlugin*>(_plugin);
    ExecutionPlugin* executionPlugin = qobject_cast<ExecutionPlugin*>(_plugin);
    if(!interfacePlugin)
    {
        if(!executionPlugin)
            return false;
        else
        {
            this->executionPlugins->append(executionPlugin);
        }
    }
    else {
        this->interfacePlugins->append(interfacePlugin);
    }

    return true;
}

QVector<InterfacePlugin *> *PluginManager::getInterfacePlugins() const
{
    return interfacePlugins;
}

QVector<ExecutionPlugin *> *PluginManager::getExecutionPlugins() const
{
    return executionPlugins;
}

QString PluginManager::getPluginDirPath() {
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("Plugins");
    return pluginsDir.absolutePath();
}
