#include "surfaceplugin.h"
#include "QApplication"
#include "QMenuBar"
#include "QSlider"
#include "objectclasses/objobject.h"

void SurfacePlugin::load()
{
    QMainWindow *window = this->getRenderingWindow();
    QMenu *menu = new QMenu("surface", window);
    QAction *action = new QAction("Open Obj File");
    menu->addAction(action);

    QMenuBar * toolbar = window->findChild<QMenuBar *>("menubar");
    toolbar->addMenu(menu);

    /// Reacts to changes in mode
    connect(action, SIGNAL(triggered()), this, SLOT(openObjFile()));
}

const char* SurfacePlugin::getType()
{
    return "surfacePlugin";
}

void SurfacePlugin::close()
{

}

SurfacePlugin::~SurfacePlugin()
{

}

void SurfacePlugin::openObjFile()
{
    QMainWindow *window = this->getRenderingWindow();
    QSlider * slider = window->findChild<QSlider *>("horizontalSlider");
    slider->hide();

    QWidget * widget = window->findChild<QWidget *>("centralwidget");
    widget->show();
    Object *object = new ObjObject();
    object->readObject();
    core->addObject(object);
    printObjects3D();
}

void SurfacePlugin::printObjects3D()
{
    QMainWindow *window = this->getRenderingWindow();
    QVTKWidget * widget = window->findChild<QVTKWidget *>("qvtkWidget");
    widget->show();

    for(Object *obj : *core->getObjects())
    {
        if(strcmp(obj->objectType(), "Obj") == 0)
        {
            obj->printObject(widget);
        }
    }
}
