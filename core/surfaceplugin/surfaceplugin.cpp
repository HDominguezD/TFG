#include "surfaceplugin.h"
#include "QMenuBar"

void SurfacePlugin::load()
{
    QMainWindow *window = this->getRenderingWindow();
    QMenu *menu = new QMenu("surface", window);
    QAction *action = new QAction("Open Obj File");
    menu->addAction(action);

    QMenuBar *toolbar = renderingWindow->findChild<QMenuBar *>("menubar");
    toolbar->addMenu(menu);

    windows = new QVector<SurfaceWindow*>();

    connect(action, SIGNAL(triggered()), this, SLOT(openObjFile()));
}

const char* SurfacePlugin::getType()
{
    return "interfacePlugin";
}

void SurfacePlugin::close()
{

}

SurfacePlugin::~SurfacePlugin()
{

}

void SurfacePlugin::openObjFile()
{

    SurfaceWindow *dock = new SurfaceWindow(renderingWindow);
    dock->setAllowedAreas(Qt::AllDockWidgetAreas);
    dock->setCore(core);
    dock->setRenderingWindow(renderingWindow);
    bool initialized = dock->initialize();

    if(initialized)
    {
        if(core->getTabs()->size() == 1)
        {
            renderingWindow->addDockWidget(Qt::TopDockWidgetArea, dock);
            windows->append(dock);
        }
        else
        {
            renderingWindow->tabifyDockWidget(core->getTabs()->at(core->getTabs()->size() -2), dock);
            windows->append(dock);
            dock->setVisible(true);
            dock->setFocus();
            dock->raise();
        }
    }
    else
    {
        core->removeTab(dock);
    }
}
