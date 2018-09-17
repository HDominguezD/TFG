#include "loaddata.h"
#include "ui_loaddata.h"
#include "renderingwindow.h"
#include "objreader.h"
#include <qfiledialog.h>
#include "ObjectClasses/objobject.h"

LoadData::LoadData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadData)
{
    ui->setupUi(this);
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
    ObjObject* object = new ObjObject();
    object->readObjectFromFile(filename);

    RenderingWindow* w = new RenderingWindow();
    w->printObjObject(object);
    w->show();
    ui->mesh->setDisabled(true);


}

void LoadData::on_volumetric_clicked(bool checked)
{
    if(checked)
    {
        RenderingWindow* w = new RenderingWindow();
        w->show();
        ui->volumetric->setDisabled(true);
    }
}

void LoadData::on_image_clicked(bool checked)
{
    if(checked)
    {
        RenderingWindow* w = new RenderingWindow();
        w->show();
        ui->image->setDisabled(true);
    }
}
