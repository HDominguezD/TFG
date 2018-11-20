#ifndef IMAGEPLUGIN_H
#define IMAGEPLUGIN_H
#include "plugins/plugin.h"
#include "QSlider"

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
    void printObjects2D();
    void initializateSlider();
    QSlider *slider;
    QWidget *widget;
    QVTKWidget *vtkWidget;
    QMenuBar * toolbar;

private slots:
    void openTifFile();
    void openTifStack();
    void changeImageShowed(int value);
};

#endif // SURFACEPLUGIN_H
