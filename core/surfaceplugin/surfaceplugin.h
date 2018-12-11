#ifndef SURFACEPLUGIN_H
#define SURFACEPLUGIN_H
#include "plugins/plugin.h"

class SurfacePlugin : public QObject, Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "application.plugin/2.0" FILE "surfaceplugin.json")
    Q_INTERFACES(Plugin)

public:
    void load();
    const char* getType();
    void close();
    virtual ~SurfacePlugin();

private:
    QWidget *widget;
    QWidget *window;

private slots:
    void openObjFile();
};

#endif // SURFACEPLUGIN_H
