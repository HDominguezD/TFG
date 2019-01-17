#ifndef VOLUMEPLUGIN_H
#define VOLUMEPLUGIN_H
#include "plugins/plugin.h"
#include "QSlider"

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
    void initializeSlider(QSlider *slider);
    QWidget *widget;
    QWidget *window;
    int lastValue;

private slots:
    void changeObjScale(int value);
    void openTifStack();
    void openObjFile();
    void captureImage();
};

#endif // VOLUMEPLUGIN_H
