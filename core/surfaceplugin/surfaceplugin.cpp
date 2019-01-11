#include "surfaceplugin.h"
#include "QApplication"
#include "QMenuBar"
#include "QSlider"
#include "objectclasses/objobject.h"
#include "QDockWidget"
#include "QVBoxLayout"
#include "QDesktopWidget"

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

        QDesktopWidget *desktop = QApplication::desktop();

        QSize min(desktop->width() /2 -100, desktop->height() /2 -100);
        dock->setMinimumSize(min);
        QSize max(desktop->width() -200, desktop->height() -200);
        dock->setMaximumSize(max);

        QSizePolicy policy(QSizePolicy::Ignored, QSizePolicy::Ignored, QSizePolicy::DefaultType);
        vtkWidget->setSizePolicy(policy);

        core->addObject(object);
        core->addTab(window);

        object->printObject(vtkWidget);
    }
}
