#ifndef VOLUMEPLUGIN_H
#define VOLUMEPLUGIN_H
#include "plugins/plugin.h"

class VolumePlugin : public QObject, Plugin
{

    Q_OBJECT
    Q_PLUGIN_METADATA(IID "application.plugin/2.0" FILE "volumeplugin.json")
    Q_INTERFACES(Plugin)

public:
    void load();
    const char* getType();
    void close();
    virtual ~VolumePlugin();

private:
    QWidget *widget;
    QTabWidget * tab;
    QWidget *window;

private slots:
    void openTifStack();
};

#endif // VOLUMEPLUGIN_H
