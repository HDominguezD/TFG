#include "volumeplugin.h"
#include "QApplication"
#include "QMenuBar"
#include "QSlider"
#include "objectclasses/tifvolumeobject.h"
#include "objectclasses/objobject.h"
#include "QDockWidget"
#include "QVBoxLayout"
#include "QPushButton"
#include "QDesktopWidget"
#include "vtkRenderWindow.h"
#include "vtkRendererCollection.h"
#include "vtkActorCollection.h"
#include "vtkTransform.h"
#include "boost/algorithm/string.hpp"
#include "QKeyEvent"
#include "myqvtkwidget.h"
#include "vtkWindowToImageFilter.h"
#include "vtkPNGWriter.h"
#include "qfiledialog.h"
#include "Editors/transferFunctionEditor.h"
#include "QHBoxLayout"
#include "QRect"
#include "QMainWindow"
#include "Editors/transformeditorObject.h"

void VolumePlugin::load()
{
    QMenu *menu = new QMenu("volume", renderingWindow);
    QAction *action = new QAction("open tifs directory");
    menu->addAction(action);

    QMenuBar *toolbar = renderingWindow->findChild<QMenuBar *>("menubar");
    toolbar->addMenu(menu);

    windows = new QVector<VolumeWindow*>();

    connect(action, SIGNAL(triggered()), this, SLOT(openTifStack()));
}

const char* VolumePlugin::getType()
{
    return "interfacePlugin";
}

void VolumePlugin::close()
{

}

VolumePlugin::~VolumePlugin()
{

}

void VolumePlugin::openTifStack()
{
    VolumeWindow *dock = new VolumeWindow(renderingWindow);
    dock->setAllowedAreas(Qt::AllDockWidgetAreas);
    dock->setRenderingWindow(renderingWindow);
    dock->setCore(core);
    bool initialized = dock->initialize();

    if(initialized){
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
