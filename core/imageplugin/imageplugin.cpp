#include "imageplugin.h"
#include "QApplication"
#include "QMenuBar"
#include "objectclasses/tifobject.h"
#include "objectclasses/tifstackobject.h"
#include <QObject>
#include "vtkImageSliceCollection.h"
#include "QVBoxLayout"

void ImagePlugin::load()
{
    QMenu *menu = new QMenu("image", renderingWindow);
    QAction *action = new QAction("Open tif File");
    menu->addAction(action);
    QAction *action2 = new QAction("Open tif Stack Directory");
    menu->addAction(action2);

    connect(action, SIGNAL(triggered()), this, SLOT(openTifFile()));
    connect(action2, SIGNAL(triggered()), this, SLOT(openTifStack()));

    widget = renderingWindow->findChild<QWidget *>("centralwidget");
    QMenuBar *toolbar = renderingWindow->findChild<QMenuBar *>("menubar");
    toolbar->addMenu(menu);
    tab = renderingWindow->findChild<QTabWidget *>("tabWidget");
    tab->setMinimumHeight(602);
    tab->setMinimumWidth(811);
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
    Object *object = new TifObject();
    if(object->readObject())
    {
        window = new QWidget();
        widget->show();

        QVTKWidget *vtkWidget = new QVTKWidget(window, 0);
        vtkWidget->setObjectName("qvtkWidget");
        vtkWidget->setFixedHeight(580);
        vtkWidget->setFixedWidth(789);

        const QString name = QObject::tr("tif Image");
        tab->addTab(window, name);

        core->addObject(object);
        core->addTab(window);

        object->printObject(vtkWidget);
    }
}

void ImagePlugin::openTifStack()
{
    Object *object = new TifStackObject();
    if(object->readObject())
    {
        widget->show();
        window = new QWidget();

        QVTKWidget *vtkWidget = new QVTKWidget();
        vtkWidget->setObjectName("qvtkWidget");
        vtkWidget->setFixedHeight(500);
        vtkWidget->setFixedWidth(500);

        slider = new QSlider(Qt::Orientation::Horizontal);
        slider->setObjectName("slider");
        slider->setFixedWidth(500);

        QVBoxLayout *layout = new QVBoxLayout(window);
        layout->addWidget(vtkWidget);
        layout->addWidget(slider);

        const QString name = QObject::tr("tif Stack");
        tab->addTab(window, name);

        core->addObject(object);
        core->addTab(window);

        initializateSlider(object);

        object->printObject(vtkWidget);
    }
}

void ImagePlugin::changeImageShowed(int value)
{
    int activeObject = tab->currentIndex();
    if( !core->getObjects()->isEmpty() && !core->getTabs()->isEmpty()){
        Object *object = core->getObjects()->at(activeObject);
        if(strcmp(object->objectType(),"TifStack") == 0){
            TifStackObject *obj = dynamic_cast<TifStackObject*>(object);
            obj->setActiveImage(value);
            QWidget *actualTab = core->getTabs()->at(activeObject);
            QVTKWidget *vtkWindow = actualTab->findChild<QVTKWidget *>("qvtkWidget");
            obj->printObject(vtkWindow);
        }
    }
}

void ImagePlugin::initializateSlider(Object *object)
{
    if(strcmp(object->objectType(),"TifStack") == 0){
        TifStackObject *obj = dynamic_cast<TifStackObject*>(object);
        slider->setMaximum(obj->getTifStack()->size() - 1);
        slider->setMinimum(0);
        slider->setValue(0);
        obj->setActiveImage(0);
        connect(slider, SIGNAL(valueChanged(int)), this, SLOT(changeImageShowed(int)));
    }
}
