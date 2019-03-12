#ifndef VOLUMEPLUGIN_H
#define VOLUMEPLUGIN_H
#include "plugins/interfaceplugin.h"
#include "QSlider"
#include "objectclasses/tifvolumeobject.h"
#include "objectclasses/objobject.h"
#include "vtkCamera.h"
#include "QVector"
#include "volumewindow.h"

class VolumePlugin : public QObject, InterfacePlugin
{

    Q_OBJECT
    Q_PLUGIN_METADATA(IID "application.plugin/2.0" FILE "volumeplugin.json")
    Q_INTERFACES(InterfacePlugin)

public:
    void load();
    const char* getType();
    void close();
    virtual ~VolumePlugin();

private:
    QVector<VolumeWindow*> *windows;

private slots:
    void openTifStack();
};

#endif // VOLUMEPLUGIN_H
