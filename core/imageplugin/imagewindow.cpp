#include "imagewindow.h"
#include "QApplication"
#include "QMenuBar"
#include "objectclasses/tifobject.h"
#include "objectclasses/tifstackobject.h"
#include <QObject>
#include "vtkImageSliceCollection.h"
#include "QVBoxLayout"
#include "QDesktopWidget"
#include "boost/algorithm/string.hpp"

ImageWindow::ImageWindow(QWidget *parent) : QDockWidget(parent)
{
    setParent(parent);
    setWindowTitle("Image Scene");
    slider = new QSlider();
}

bool ImageWindow::initializeTif()
{
    object = new TifObject();
    bool initialized = object->readObject();

    if(initialized)
    {
        vtkWidget = new QVTKWidget();

        QWidget *window = new QWidget();

        QVBoxLayout *layout = new QVBoxLayout(window);
        layout->setGeometry(window->geometry());
        layout->addWidget(vtkWidget);

        TifObject *obj = dynamic_cast<TifObject*>(object);

        int *dims = obj->getDimensions();
        if(dims[2] > 1){
            slider = new QSlider(Qt::Orientation::Horizontal);
            //slider->hide();

            layout->addWidget(slider);

            initializeSlider();
        }

        this->setWidget(window);

        core->addObject(object);

        QDesktopWidget *desktop = QApplication::desktop();

        QSize min(desktop->width() /2 -100, desktop->height() /2 -100);
        this->setMinimumSize(min);
        QSize max(desktop->width() -200, desktop->height() -200);
        this->setMaximumSize(max);

        QSizePolicy policy(QSizePolicy::Ignored, QSizePolicy::Ignored, QSizePolicy::DefaultType);
        vtkWidget->setSizePolicy(policy);
        obj->resizeImage(vtkWidget);
        object->printObject(vtkWidget);
    }

    return initialized;
}

bool ImageWindow::initializeTifStack()
{
    object = new TifStackObject();
    bool initialized = object->readObject();

    if(initialized)
    {
        vtkWidget = new QVTKWidget();

        slider = new QSlider(Qt::Orientation::Horizontal);

        QWidget *window = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(window);
        layout->setGeometry(window->geometry());
        layout->addWidget(vtkWidget);
        layout->addWidget(slider);

        this->setWidget(window);

        core->addObject(object);

        initializeSlider();

        QDesktopWidget *desktop = QApplication::desktop();

        QSize min(desktop->width() /2 -100, desktop->height() /2 -100);
        this->setMinimumSize(min);
        QSize max(desktop->width() -200, desktop->height() -200);
        this->setMaximumSize(max);

        QSizePolicy policy(QSizePolicy::Ignored, QSizePolicy::Ignored, QSizePolicy::DefaultType);
        vtkWidget->setSizePolicy(policy);

        TifStackObject *objs = dynamic_cast<TifStackObject*>(object);
        for(int i = 0; i < objs->getTifStack()->size(); i++)
        {
            objs->getTifStack()->at(i)->resizeImage(vtkWidget);
        }

        object->printObject(vtkWidget);
    }

    return initialized;
}

void ImageWindow::setCore(Core *value)
{
    core = value;
    core->addTab(this);
}

RenderingWindow *ImageWindow::getRenderingWindow() const
{
    return renderingWindow;
}

void ImageWindow::setRenderingWindow(RenderingWindow *value)
{
    renderingWindow = value;
}

void ImageWindow::initializeSlider()
{
    if(strcmp(object->objectType(),"TifStack") == 0)
    {
        TifStackObject *obj = dynamic_cast<TifStackObject*>(object);
        slider->setMaximum(obj->getTifStack()->size() - 1);
        slider->setMinimum(0);
        slider->setValue(0);
        obj->setActiveImage(0);
        connect(slider, SIGNAL(valueChanged(int)), this, SLOT(changeImageShowed(int)));
    }

    if(strcmp(object->objectType(),"Tif") == 0)
    {
        //slider->show();
        TifObject *obj = dynamic_cast<TifObject*>(object);
        int dim = obj->getDimensions()[2];
        slider->setMaximum(obj->getDimensions()[2] - 1);
        slider->setMinimum(0);
        slider->setValue(0);
        obj->setActiveImage(0);
        connect(slider, SIGNAL(valueChanged(int)), this, SLOT(changeImageShowed(int)));
    }
}

void ImageWindow::changeImageShowed(int value)
{
    if(object)
    {
        if(strcmp(object->objectType(),"Tif") == 0)
        {
            TifObject *obj = dynamic_cast<TifObject*>(object);
            obj->setActiveImage(value);
            obj->printObject(vtkWidget);
        }

        if(strcmp(object->objectType(),"TifStack") == 0)
        {
            TifStackObject *obj = dynamic_cast<TifStackObject*>(object);
            obj->setActiveImage(value);
            obj->printObject(vtkWidget);
        }
    }
}
