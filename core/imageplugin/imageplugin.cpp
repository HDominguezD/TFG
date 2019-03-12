#include "imageplugin.h"
#include "QMenuBar"

void ImagePlugin::load()
{
    QMenu *menu = new QMenu("image", renderingWindow);
    QAction *action = new QAction("Open tif File");
    menu->addAction(action);
    QAction *action2 = new QAction("Open tif Stack Directory");
    menu->addAction(action2);
    QMenuBar *toolbar = renderingWindow->findChild<QMenuBar *>("menubar");
    toolbar->addMenu(menu);

    windows = new QVector<ImageWindow*>();

    connect(action, SIGNAL(triggered()), this, SLOT(openTifFile()));
    connect(action2, SIGNAL(triggered()), this, SLOT(openTifStack()));
}

const char* ImagePlugin::getType()
{
    return "interfacePlugin";
}

void ImagePlugin::close()
{

}

ImagePlugin::~ImagePlugin()
{

}

void ImagePlugin::openTifFile()
{
    ImageWindow *dock = new ImageWindow(renderingWindow);
    dock->setAllowedAreas(Qt::AllDockWidgetAreas);
    dock->setRenderingWindow(renderingWindow);
    dock->setCore(core);
    bool initialized = dock->initializeTif();

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

void ImagePlugin::openTifStack()
{
    ImageWindow *dock = new ImageWindow(renderingWindow);
    dock->setAllowedAreas(Qt::AllDockWidgetAreas);
    dock->setRenderingWindow(renderingWindow);
    dock->setCore(core);
    bool initialized = dock->initializeTifStack();

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
