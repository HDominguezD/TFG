#include "renderingwindow.h"
#include "ui_renderingwindow.h"
#include "objectclasses/abstractclasses/object.h"
#include "objectclasses/tifvolumeobject.h"
#include <vtkSmartPointer.h>
#include <vtkPolygon.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRendererCollection.h>
#include <vtkImageResize.h>
#include <vtkImageData.h>
#include <qfiledialog.h>
#include <vtkActor2D.h>
#include <vtkObjectBase.h>
#include <boost/algorithm/string.hpp>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkCamera.h>
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
    for(Plugin* plugin : *manager->getPlugins()){
        // qDebug() << "GuiPlugin::load " << plugin->name();
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

void RenderingWindow::printObjects3D()
{

    ui->centralwidget->show();


    for(Object *obj : *core->getObjects3D())
    {
        if(strcmp(obj->objectType(), "Obj") == 0)
        {
            obj->printObject(ui->qvtkWidget);
        }
    }
}

void RenderingWindow::printVolObjects()
{
    ui->centralwidget->show();

    for(Object *obj : *core->getVolObjects())
    {
        if(strcmp(obj->objectType(), "TifVolume") == 0){
            obj->printObject(ui->qvtkWidget);
        }
    }
}

void RenderingWindow::printObjects2D()
{
    ui->centralwidget->show();

    for(Object *obj : *core->getObjects2D())
    {
        if(strcmp(obj->objectType(), "Tif") == 0){
            obj->printObject(ui->qvtkWidget);
        }
        else if(strcmp(obj->objectType(), "TifStack") == 0){
            obj->printObject(ui->qvtkWidget);
        }
    }
}

void RenderingWindow::on_actionopen_file_triggered()
{
    ui->horizontalSlider->hide();
    ui->centralwidget->show();
    Object *object = new ObjObject();
    object->readObject();
    core->addObject3D(object);
    printObjects3D();
}

void RenderingWindow::on_actionopen_stack_of_files_triggered()
{
    ui->centralwidget->show();
    ui->horizontalSlider->show();
    Object *object = new TifObject();
    object->readObject();
    core->addObject2D(object);
    initializateSlider();
}

//void RenderingWindow::on_horizontalSlider_valueChanged(int value)
//{

//    core->getObjects2D()->at(value)->printObject(ui->qvtkWidget);
//}

void RenderingWindow::initializateSlider()
{
    ui->centralwidget->show();

    if(core->getObjects2D() != nullptr)
    {
        ui->horizontalSlider->setMaximum(core->getObjects2D()->size() - 1);
        ui->horizontalSlider->setMinimum(0);
        ui->horizontalSlider->setValue(0);

        core->getObjects2D()->at(0)->printObject(ui->qvtkWidget);
    }
}

void RenderingWindow::showOnlyToolBar()
{
    QRect geometry = this->geometry();
    geometry.setHeight(20);
    this->setGeometry(geometry);

    ui->centralwidget->hide();
    ui->horizontalSlider->hide();
}

Ui::RenderingWindow *RenderingWindow::getUi() const
{
    return ui;
}

void RenderingWindow::on_actionopen_tif_Volume_triggered()
{
    ui->horizontalSlider->hide();

    Object *obj = new TifVolumeObject();
    obj->readObject();
    core->addVolObject(obj);

    printVolObjects();
}

void RenderingWindow::on_actionopen_tif_file_triggered()
{
    ui->horizontalSlider->hide();
    ui->centralwidget->show();

    Object *object = new TifObject();
    object->readObject();
    core->addObject2D(object);
    this->printObjects2D();
}
