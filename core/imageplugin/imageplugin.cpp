#include "imageplugin.h"
#include "QApplication"
#include "QMenuBar"
#include "objectclasses/tifobject.h"
#include "objectclasses/tifstackobject.h"
#include <QObject>
#include "vtkImageSliceCollection.h"

void ImagePlugin::load()
{
    QMenu *menu = new QMenu("image", renderingWindow);
    QAction *action = new QAction("Open tif File");
    menu->addAction(action);

    vtkWidget = renderingWindow->findChild<QVTKWidget *>("qvtkWidget");
    slider = renderingWindow->findChild<QSlider *>("horizontalSlider");
    widget = renderingWindow->findChild<QWidget *>("centralwidget");
    toolbar = renderingWindow->findChild<QMenuBar *>("menubar");

    toolbar->addMenu(menu);

    /// Reacts to changes in mode
    connect(action, SIGNAL(triggered()), this, SLOT(openTifFile()));

    QAction *action2 = new QAction("Open tif Stack Directory");
    menu->addAction(action2);

    toolbar->addMenu(menu);

    /// Reacts to changes in mode
    connect(action2, SIGNAL(triggered()), this, SLOT(openTifStack()));
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(changeImageShowed(int)));
}

const char* ImagePlugin::getType()
{
    return "imagePlugin";
}

void ImagePlugin::close()
{

}

ImagePlugin::~ImagePlugin()
{

}

void ImagePlugin::openTifFile()
{
    slider->hide();
    widget->show();

    Object *object = new TifObject();
    object->readObject();
    core->addObject2D(object);
    printObjects2D();
}

void ImagePlugin::openTifStack()
{
    slider->show();
    widget->show();

    Object *object = new TifStackObject();
    object->readObject();
    core->addObject2D(object);
    initializateSlider();
}


void ImagePlugin::printObjects2D()
{
    vtkWidget->show();

    for(Object *obj : *core->getObjects2D())
    {
        if(strcmp(obj->objectType(), "Tif") == 0)
        {
            obj->printObject(vtkWidget);
        }
        if(strcmp(obj->objectType(), "TifStack") == 0)
        {
            obj->printObject(vtkWidget);
        }
    }
}


void ImagePlugin::changeImageShowed(int value)
{
    if(core->getObjects2D() != nullptr)
    {
        if(strcmp(core->getObjects2D()->at(0)->objectType(),"TifStack") == 0){
            TifStackObject *obj = dynamic_cast<TifStackObject*>(core->getObjects2D()->at(0));
            obj->setActiveImage(value);
            obj->printObject(vtkWidget);
        }
    }
}

void ImagePlugin::initializateSlider()
{
    if(core->getObjects2D() != nullptr)
    {
        if(strcmp(core->getObjects2D()->at(0)->objectType(),"TifStack") == 0){
            TifStackObject *obj = dynamic_cast<TifStackObject*>(core->getObjects2D()->at(0));
            slider->setMaximum(obj->getTifStack()->size() - 1);
            slider->setMinimum(0);
            slider->setValue(0);
            obj->setActiveImage(0);
            obj->printObject(vtkWidget);
        }
    }
}
