#ifndef IMAGEPLUGIN_H
#define IMAGEPLUGIN_H
#include "plugins/interfaceplugin.h"
#include "imagewindow.h"

class ImagePlugin : public QObject, InterfacePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "application.plugin/2.0" FILE "imageplugin.json")
    Q_INTERFACES(InterfacePlugin)

public:
    void load();
    const char* getType();
    void close();
    virtual ~ImagePlugin();

private:
    QVector<ImageWindow*> *windows;

private slots:
    void openTifFile();
    void openTifStack();
};

#endif // SURFACEPLUGIN_H
