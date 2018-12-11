#include "volumeplugin.h"
#include "QApplication"
#include "QMenuBar"
#include "QSlider"
#include "objectclasses/tifvolumeobject.h"
#include "QDockWidget"
#include "QHBoxLayout"
#include "QPushButton"

void VolumePlugin::load()
{
    QMenu *menu = new QMenu("volume", renderingWindow);
    QAction *action = new QAction("open tifs directory");
    menu->addAction(action);

    widget = renderingWindow->findChild<QWidget *>("centralwidget");
    QMenuBar *toolbar = renderingWindow->findChild<QMenuBar *>("menubar");
    toolbar->addMenu(menu);

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
    Object *object = new TifVolumeObject();
    if(object->readObject())
    {
        QList<QDockWidget*> docks = renderingWindow->findChildren<QDockWidget*>();

        QDockWidget *dock = new QDockWidget(tr("Volume Object"), renderingWindow);
        dock->setAllowedAreas(Qt::AllDockWidgetAreas);

        if(docks.isEmpty()){
            renderingWindow->addDockWidget(Qt::RightDockWidgetArea, dock);
        }
        else {
            renderingWindow->tabifyDockWidget(docks.at(docks.size() -1), dock);
        }

        QVTKWidget *vtkWidget = new QVTKWidget();
        vtkWidget->setObjectName("QVTKWidget");

        window = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(window);
        layout->addWidget(vtkWidget);

        QPushButton *compare = new QPushButton();
        compare->setText("Compare with 3D Model");
        layout->addWidget(compare);

        dock->setWidget(window);

        QSize min(window->width() /2, window->height() /2);
        dock->setMinimumSize(min);

        core->addObject(object);
        core->addTab(window);

        object->printObject(vtkWidget);
    }
}
