#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkInteractionStyle);

#include "renderingwindow.h"
#include "ui_renderingwindow.h"
#include "objectclasses/abstractclasses/object.h"
#include "objectclasses/tifvolumeobject.h"
#include "pluginmanager/pluginmanager.h"
#include "qdesktopwidget.h"
#include "QScrollArea"

using namespace std;

RenderingWindow::RenderingWindow(QWidget *parent, Core *core) :
    QMainWindow(parent),
    ui(new Ui::RenderingWindow)
{
    ui->setupUi(this);

    showOnlyToolBar();
    this->core = core;

    PluginManager *manager = new PluginManager();
    manager->loadPlugins();

//    for(ExecutionPlugin *plugin : *manager->getExecutionPlugins()){
//        plugin->setRenderingWindow(this);
//        plugin->setCore(core);
//        plugin->load();
//    }

    for(InterfacePlugin *plugin : *manager->getInterfacePlugins()){
        plugin->setRenderingWindow(this);
        plugin->setCore(core);
        plugin->load();
    }

    QDesktopWidget *desktop = QApplication::desktop();

    int screenWidth, width;
    int screenHeight, height;
    int x, y;
    QSize windowSize;

    screenWidth = desktop->width(); // get width of screen
    screenHeight = desktop->height(); // get height of screen

    windowSize = size(); // size of our application window
    width = windowSize.width();
    height = windowSize.height();

    // little computations
    x = (screenWidth - width) / 2;
    y = (height);
    y += 100;

    // move window to desired coordinates
    move ( x, y );
}

RenderingWindow::~RenderingWindow()
{
    delete ui;
    delete core;
}

void RenderingWindow::showOnlyToolBar()
{
    QRect geometry = this->geometry();
    geometry.setHeight(20);
    this->setGeometry(geometry);

    ui->centralwidget->hide();
}
