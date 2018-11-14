#include "surfaceplugin.h"
#include "QApplication"
#include "QMenuBar"
#include "QSlider"
#include "../applicationlib/objectclasses/objobject.h"

void SurfacePlugin::load()
{
    QMainWindow *window = this->getRenderingWindow();
    QMenu *menu = new QMenu("surface", window);
    QAction *action = new QAction("Open Obj File");
    menu->addAction(action);

    QMenuBar * toolbar = window->findChild<QMenuBar *>("menubar");
    toolbar->addMenu(menu);

    /// Reacts to changes in mode
    connect(action, SIGNAL(triggered()), this, SLOT(open()));
}

const char* SurfacePlugin::getType()
{
    return "surfacePlugin";
}

void SurfacePlugin::close()
{
    int hola = 1;
}

void SurfacePlugin::open()
{
    QMainWindow *window = this->getRenderingWindow();
    QSlider * slider = window->findChild<QSlider *>("horizontalSlider");
    slider->hide();

    QWidget * widget = window->findChild<QWidget *>("centralwidget");
    widget->show();
    Object *object = new ObjObject();
    object->readObject();
    core = new Core();
    core->addObject3D(object);
    printObjects3D();
}

void SurfacePlugin::printObjects3D()
{
    QMainWindow *window = this->getRenderingWindow();
    QVTKWidget * widget = window->findChild<QVTKWidget *>("qvtkWidget");
    widget->show();

    for(Object *obj : *core->getObjects3D())
    {
        if(strcmp(obj->objectType(), "obj") == 0)
        {
            obj->printObject(widget);
        }
    }
}
