#include "loaddata.h"
#include "ui_loaddata.h"
#include "renderingwindow.h"
#include "objreader.h"
#include <qfiledialog.h>
#include "ObjectClasses/objobject.h"

LoadData::LoadData(QWidget *parent , Core *core) :
    QWidget(parent),
    ui(new Ui::LoadData)
{
    ui->setupUi(this);
    this->core = core;
}

LoadData::~LoadData()
{
    delete ui;
}

void LoadData::on_mesh_clicked(bool checked)
{
//    if(!checked)
//    {
//        RenderingWindow* w = new RenderingWindow();
//        w->show();
//        ui->mesh->setDisabled(true);
//    }

//    ObjReader* reader = new ObjReader();

    QStringList fileNames = QFileDialog::getOpenFileNames( Q_NULLPTR, QObject::tr("Open File"),"/path/to/file/",QObject::tr("Mesh Files (*.obj)"));
    std::string filename = fileNames.at(0).toStdString();
    Object3D* object = new ObjObject();
    object->readObjectFromFile(filename);
    core->addObject(object);
    QWidget *parent = 0;
    RenderingWindow* w = new RenderingWindow(parent, core);
    w->printObjects();
    w->show();
    ui->mesh->setDisabled(true);


}

void LoadData::on_volumetric_clicked(bool checked)
{
    if(checked)
    {
        QWidget *parent = 0;
        RenderingWindow* w = new RenderingWindow(parent, core);w->show();
        ui->volumetric->setDisabled(true);
    }
}

void LoadData::on_image_clicked(bool checked)
{
    if(checked)
    {
        QWidget *parent = 0;
        RenderingWindow* w = new RenderingWindow(parent, core);w->show();
        ui->image->setDisabled(true);
    }
}
