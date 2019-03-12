#ifndef SURFACEPLUGIN_H
#define SURFACEPLUGIN_H
#include "plugins/interfaceplugin.h"
#include "surfacewindow.h"

class SurfacePlugin : public QObject, InterfacePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "application.plugin/2.0" FILE "surfaceplugin.json")
    Q_INTERFACES(InterfacePlugin)

public:
    void load();
    const char* getType();
    void close();
    virtual ~SurfacePlugin();

private:
    QVector<SurfaceWindow*> *windows;

private slots:
    void openObjFile();
};

#endif // SURFACEPLUGIN_H
