#ifndef IMAGEPLUGIN_H
#define IMAGEPLUGIN_H
#include "plugins/plugin.h"
#include "QSlider"
#include "QTabWidget"

class ImagePlugin : public QObject, Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "application.plugin/2.0" FILE "imageplugin.json")
    Q_INTERFACES(Plugin)

public:
    void load();
    const char* getType();
    void close();
    virtual ~ImagePlugin();

private:
    void initializateSlider(Object *obj);
    QWidget *widget;
    QSlider *slider;
    QTabWidget * tab;
    QWidget *window;

private slots:
    void openTifFile();
    void openTifStack();
    void changeImageShowed(int value);
};

#endif // SURFACEPLUGIN_H
