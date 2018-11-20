#include "renderingwindow.h"
#include "ui_renderingwindow.h"
#include "objectclasses/abstractclasses/object.h"
#include "objectclasses/tifvolumeobject.h"
#include "pluginmanager/pluginmanager.h"

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
    for(Plugin *plugin : *manager->getPlugins()){
        plugin->setRenderingWindow(this);
        plugin->setCore(core);
        plugin->load();
    }

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
    ui->horizontalSlider->hide();
}
