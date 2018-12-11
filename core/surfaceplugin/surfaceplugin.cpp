#include "surfaceplugin.h"
#include "QApplication"
#include "QMenuBar"
#include "QSlider"
#include "objectclasses/objobject.h"
#include "QDockWidget"
#include "QVBoxLayout"

void SurfacePlugin::load()
{
    QMainWindow *window = this->getRenderingWindow();
    QMenu *menu = new QMenu("surface", window);
    QAction *action = new QAction("Open Obj File");
    menu->addAction(action);

    widget = renderingWindow->findChild<QWidget *>("centralwidget");
    QMenuBar *toolbar = renderingWindow->findChild<QMenuBar *>("menubar");
    toolbar->addMenu(menu);
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
    Object *object = new ObjObject();
    if(object->readObject())
    {
        QList<QDockWidget*> docks = renderingWindow->findChildren<QDockWidget*>();

        QDockWidget *dock = new QDockWidget(tr("Surface Object"), renderingWindow);
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
        QVBoxLayout *layout = new QVBoxLayout(window);
        layout->addWidget(vtkWidget);

        dock->setWidget(window);

        QSize min(window->width() /2, window->height() /2);
        dock->setMinimumSize(min);

        core->addObject(object);
        core->addTab(window);

        object->printObject(vtkWidget);
    }
}
