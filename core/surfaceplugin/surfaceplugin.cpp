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

    widget = renderingWindow->findChild<QWidget *>("centralwidget");
    QMenuBar *toolbar = renderingWindow->findChild<QMenuBar *>("menubar");
    toolbar->addMenu(menu);
    tab = renderingWindow->findChild<QTabWidget *>("tabWidget");
    tab->setMinimumHeight(602);
    tab->setMinimumWidth(811);

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
        window = new QWidget();
        widget->show();

        QVTKWidget *vtkWidget = new QVTKWidget(window, 0);
        vtkWidget->setObjectName("qvtkWidget");
        vtkWidget->setFixedHeight(580);
        vtkWidget->setFixedWidth(789);

        const QString name = QObject::tr("Obj object");
        tab->addTab(window, name);

        core->addObject(object);
        core->addTab(window);

        object->printObject(vtkWidget);
    }
}
