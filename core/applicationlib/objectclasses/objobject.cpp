//#include "vtkAutoInit.h"
//VTK_MODULE_INIT(vtkRenderingOpenGL2);
//VTK_MODULE_INIT(vtkRenderingFreeType);
//VTK_MODULE_INIT(vtkInteractionStyle);
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
#include "vtkAxesActor.h"


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

    vector<string> splitName;
    boost::split(splitName, fileName, [](char c){return c == '/';});
    name = splitName.at(splitName.size() - 1);

    return true;
}

void ObjObject::setName(const string &value)
{
    name = value;
}

QVTKWidget *ObjObject::getVtkWidget() const
{
    return vtkWidget;
}

string ObjObject::getName() const
{
    return name;
}

vtkSmartPointer<vtkAxesActor> ObjObject::getAxes() const
{
    return axes;
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

    axes = vtkSmartPointer<vtkAxesActor>::New();
    axes->AxisLabelsOff();

    vtkSmartPointer<vtkTransform> axesTransform = vtkSmartPointer<vtkTransform>::New();
    axesTransform->Translate(-axes->GetCenter()[0], -axes->GetCenter()[1], -axes->GetCenter()[2]);
    axes->SetUserTransform(axesTransform);

    double bounds[3];
    bounds[0] = actor->GetBounds()[0];
    bounds[1] = actor->GetBounds()[1];
    bounds[2] = actor->GetBounds()[2];

    double minorBound = bounds[0];
    for(int i = 1; i < 3; i++)
    {
      if (minorBound > bounds[i])
          minorBound = bounds[i];
    }
    double sca = std::abs(minorBound)/ 8;
    axes->SetTotalLength(sca, sca, sca);
    axes->SetOrientation(actor->GetOrientation());

    renderer->AddActor(axes);
    renderer->ResetCamera();

    widget->GetRenderWindow()->GetRenderers()->RemoveAllItems();
    widget->GetRenderWindow()->AddRenderer(renderer);
    widget->GetRenderWindow()->Render();

    vtkWidget = widget;
}

const char* ObjObject::objectType()
{
    return "Obj";
}

ObjObject::~ObjObject()
{
    actor->VisibilityOff();
    axes->VisibilityOff();
}

