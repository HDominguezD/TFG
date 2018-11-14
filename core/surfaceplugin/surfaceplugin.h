#ifndef SURFACEPLUGIN_H
#define SURFACEPLUGIN_H
#include "../applicationlib/plugins/plugin.h"

class SurfacePlugin : public QObject, Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "application.plugin/2.0" FILE "surfaceplugin.json")
    Q_INTERFACES(Plugin)

public:
    void load();
    const char* getType();
    void close();

//private:
//    void printObjects3D();

private slots:
    void open();
};

#endif // SURFACEPLUGIN_H
