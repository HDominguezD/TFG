#include "volumeplugin.h"
#include "QApplication"
#include "QMenuBar"
#include "QSlider"
#include "objectclasses/tifvolumeobject.h"

void VolumePlugin::load()
{
    QMainWindow *window = this->getRenderingWindow();
    QMenu *menu = new QMenu("volume", window);
    QAction *action = new QAction("open tifs directory");
    menu->addAction(action);

    QMenuBar * toolbar = window->findChild<QMenuBar *>("menubar");
    toolbar->addMenu(menu);

    /// Reacts to changes in mode
    connect(action, SIGNAL(triggered()), this, SLOT(openTifStack()));
}

const char* VolumePlugin::getType()
{
    return "volumePlugin";
}

void VolumePlugin::close()
{

}

VolumePlugin::~VolumePlugin()
{

}

void VolumePlugin::openTifStack()
{
    QMainWindow *window = this->getRenderingWindow();
    QSlider * slider = window->findChild<QSlider *>("horizontalSlider");
    slider->hide();

    QWidget * widget = window->findChild<QWidget *>("centralwidget");
    widget->show();
    Object *object = new TifVolumeObject();
    object->readObject();
    core->addObject(object);
    printVolumeObjects();
}

void VolumePlugin::printVolumeObjects()
{
    QMainWindow *window = this->getRenderingWindow();
    QVTKWidget * widget = window->findChild<QVTKWidget *>("qvtkWidget");
    widget->show();

    for(Object *obj : *core->getObjects())
    {
        if(strcmp(obj->objectType(), "TifVolume") == 0)
        {
            obj->printObject(widget);
        }
    }
}
