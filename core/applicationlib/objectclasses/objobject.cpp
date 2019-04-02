#include "objobject.h"
#include <boost/algorithm/string.hpp>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPolygon.h>
#include <map>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include "vtkRenderWindow.h"
#include "vtkRendererCollection.h"
#include "qfiledialog.h"
#include "vtkTransform.h"
#include "vtkActorCollection.h"
#include "vtkCamera.h"
#include "vtkOBJReader.h"
#include "vtkLinearTransform.h"


using namespace std;


ObjObject::ObjObject()
{
    actor = vtkSmartPointer<vtkActor>::New();
}

bool ObjObject::readObject()
{
    bool readed = false;
    QStringList fileNames = QFileDialog::getOpenFileNames( Q_NULLPTR, QObject::tr("Open File"),"/path/to/file/",QObject::tr("Mesh Files (*.obj)"));
    if(fileNames.isEmpty())
    {
        return readed;
    }

    string fileName = fileNames.at(0).toStdString();

    vector<string> splitName;
    boost::split(splitName, fileName, [](char c){return c == '.';});
    string ext = splitName.at(splitName.size() - 1);

   if(ext == "obj"){
       readed = readObjectFromFile(fileName);
   }
   return readed;
}

bool ObjObject::readObjectFromFile(string fileName)
{
    vtkSmartPointer<vtkOBJReader> reader = vtkSmartPointer<vtkOBJReader>::New();
    reader->SetFileName(fileName.c_str());
    reader->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(reader->GetOutput());

    actor->SetMapper(mapper);

    return true;
}

vtkSmartPointer<vtkActor> ObjObject::getActor() const
{
    return actor;
}

void ObjObject::printObject(QVTKWidget *widget)
{
    vtkSmartPointer<vtkRenderer> renderer;
    if(widget->GetRenderWindow()->GetRenderers()->GetFirstRenderer() != nullptr){
        renderer = widget->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
    } else {
        renderer = vtkSmartPointer<vtkRenderer>::New();
    }

    vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
    transform->Translate(-this->actor->GetCenter()[0], -this->actor->GetCenter()[1], -this->actor->GetCenter()[2]);
    actor->SetUserTransform(transform);

    renderer->SetBackground(.2, .2, .2);
    renderer->AddActor(actor);
    renderer->SetBackground(.2, .2, .2);

    widget->GetRenderWindow()->GetRenderers()->RemoveAllItems();
    widget->GetRenderWindow()->AddRenderer(renderer);
    widget->GetRenderWindow()->Render();
}

const char* ObjObject::objectType()
{
    return "Obj";
}

ObjObject::~ObjObject()
{

}

