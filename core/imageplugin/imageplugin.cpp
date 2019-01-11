#include "imageplugin.h"
#include "QApplication"
#include "QMenuBar"
#include "objectclasses/tifobject.h"
#include "objectclasses/tifstackobject.h"
#include <QObject>
#include "vtkImageSliceCollection.h"
#include "QVBoxLayout"
#include "QDockWidget"
#include "QDesktopWidget"
#include "boost/algorithm/string.hpp"

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
        QList<QDockWidget*> docks = renderingWindow->findChildren<QDockWidget*>();

        QDockWidget *dock = new QDockWidget(tr("Image Object"), renderingWindow);
        dock->setAllowedAreas(Qt::AllDockWidgetAreas);

        if(docks.isEmpty())
        {
            renderingWindow->addDockWidget(Qt::RightDockWidgetArea, dock);
            string nameDock = string("Dock ") + to_string(docks.size());
            dock->setObjectName(nameDock.c_str());
        }
        else
        {
            renderingWindow->addDockWidget(Qt::TopDockWidgetArea, dock);
            renderingWindow->tabifyDockWidget(docks.at(docks.size() -1), dock);
            dock->setVisible(true);
            dock->setFocus();
            dock->raise();
            string nameDock = string("Dock ") + to_string(docks.size());
            dock->setObjectName(nameDock.c_str());
        }

        QVTKWidget *vtkWidget = new QVTKWidget();
        string nameWidget = string("QVTKWidget ") + to_string(docks.size());
        vtkWidget->setObjectName(nameWidget.c_str());

        window = new QWidget();

        QVBoxLayout *layout = new QVBoxLayout(window);
        layout->setGeometry(window->geometry());
        layout->addWidget(vtkWidget);

        dock->setWidget(window);

        core->addObject(object);
        core->addTab(window);

        QDesktopWidget *desktop = QApplication::desktop();

        QSize min(desktop->width() /2 -100, desktop->height() /2 -100);
        dock->setMinimumSize(min);
        QSize max(desktop->width() -200, desktop->height() -200);
        dock->setMaximumSize(max);

        QSizePolicy policy(QSizePolicy::Ignored, QSizePolicy::Ignored, QSizePolicy::DefaultType);
        vtkWidget->setSizePolicy(policy);

        object->printObject(vtkWidget);
    }
}

void ImagePlugin::openTifStack()
{
    Object *object = new TifStackObject();
    if(object->readObject())
    {
        QList<QDockWidget*> docks = renderingWindow->findChildren<QDockWidget*>();

        QDockWidget *dock = new QDockWidget(tr("Image stack Object"), renderingWindow);
        dock->setAllowedAreas(Qt::AllDockWidgetAreas);

        if(docks.isEmpty())
        {
            renderingWindow->addDockWidget(Qt::RightDockWidgetArea, dock);
            string nameDock = string("Dock ") + to_string(docks.size());
            dock->setObjectName(nameDock.c_str());
        }
        else
        {
            renderingWindow->addDockWidget(Qt::TopDockWidgetArea, dock);
            renderingWindow->tabifyDockWidget(docks.at(docks.size() -1), dock);
            dock->setVisible(true);
            dock->setFocus();
            dock->raise();
            string nameDock = string("Dock ") + to_string(docks.size());
            dock->setObjectName(nameDock.c_str());
        }

        QVTKWidget *vtkWidget = new QVTKWidget();
        string nameWidget = string("QVTKWidget ") + to_string(docks.size());
        vtkWidget->setObjectName(nameWidget.c_str());

        slider = new QSlider(Qt::Orientation::Horizontal);
        string nameSlider = string("Slider ") + to_string(docks.size());
        slider->setObjectName(nameSlider.c_str());

        window = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(window);
        layout->setGeometry(window->geometry());
        layout->addWidget(vtkWidget);
        layout->addWidget(slider);

        dock->setWidget(window);

        core->addObject(object);
        core->addTab(window);

        initializeSlider(object);

        QDesktopWidget *desktop = QApplication::desktop();

        QSize min(desktop->width() /2 -100, desktop->height() /2 -100);
        dock->setMinimumSize(min);
        QSize max(desktop->width() -200, desktop->height() -200);
        dock->setMaximumSize(max);

        QSizePolicy policy(QSizePolicy::Ignored, QSizePolicy::Ignored, QSizePolicy::DefaultType);
        vtkWidget->setSizePolicy(policy);

        object->printObject(vtkWidget);
    }
}

void ImagePlugin::changeImageShowed(int value)
{
    if( !core->getObjects()->isEmpty() && !core->getTabs()->isEmpty())
    {
//        for(int i = 0; i < core->getTabs()->size(); i++)
//        {
//            QWidget *actualTab = core->getTabs()->at(i);
//            QSlider *slider = actualTab->findChild<QSlider *>("slider");
//            if(slider!= nullptr && slider->value() == value)
//            {
//                Object *object = core->getObjects()->at(i);
//                if(strcmp(object->objectType(),"TifStack") == 0)
//                {
//                    TifStackObject *obj = dynamic_cast<TifStackObject*>(object);
//                    obj->setActiveImage(value);
//                    QVTKWidget *vtkWindow = actualTab->findChild<QVTKWidget *>("QVTKWidget");
//                    obj->printObject(vtkWindow);
//                }
//            }
//        }

        QSlider* sliderSender = qobject_cast<QSlider*>(sender());
        string sliderName = sliderSender->objectName().toStdString();
        vector<string> splitName;
        boost::split(splitName, sliderName, [](char c){return c == ' ';});
        string number = splitName.at(splitName.size() - 1);
        int dockNumber = atoi(number.c_str());

        string nameDock = string("Dock ") + to_string(dockNumber);
        QDockWidget* dock = renderingWindow->findChild<QDockWidget*>(nameDock.c_str());

        Object *object = core->getObjects()->at(dockNumber);
        if(strcmp(object->objectType(),"TifStack") == 0)
        {
            TifStackObject *obj = dynamic_cast<TifStackObject*>(object);
            obj->setActiveImage(value);
            string nameWidget = string("QVTKWidget ") + to_string(dockNumber);
            QVTKWidget *vtkWidget = dock->findChild<QVTKWidget*>(nameWidget.c_str());
            obj->printObject(vtkWidget);
        }
    }
}

void ImagePlugin::initializeSlider(Object *object)
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
}
