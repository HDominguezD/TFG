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

using namespace std;


ObjObject::ObjObject()
{
    vertexes = vtkPoints::New();
    faces = vtkCellArray::New();
    object= vtkPolyData::New();
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
    string line;
    ifstream input(fileName.c_str(), ifstream::out);
    int nPoints = 0;
    int nFaces = 0;
    while (getline(input, line))
    {
        static map<string, int> s_mapStringValues;
            s_mapStringValues.insert(pair<string, int>(string("v "), 1));
            s_mapStringValues.insert(pair<string, int>(string("f "), 2));
            s_mapStringValues.insert(pair<string, int>(string("vn"), 3));
            s_mapStringValues.insert(pair<string, int>(string("vt"), 4));
            s_mapStringValues.insert(pair<string, int>(string("vp"), 5));
            s_mapStringValues.insert(pair<string, int>(string("l "), 6));

        string beginning = line.substr(0, 2);
        vector<string> results;
        boost::split(results, line, [](char c){return c == ' ';});

        switch (s_mapStringValues.find(beginning)->second)
        {
            case 1:
            {
                vertexes->InsertPoint(nPoints, stod(results.at(1)), stod(results.at(2)), stod(results.at(3)));

                nPoints++;
                break;
            }
            case 2:
            {
                vtkIdList *pts = vtkIdList::New();


                for(ulong i = 1; i < results.size(); i++)
                {
                    pts->InsertId(static_cast<long long> (i-1), stoi(results.at(i)) -1);

                }


                // Add the polygon to a list of polygons
                faces->InsertNextCell(pts);
                nFaces++;
                break;
            };
        }
    }

    // Create a PolyData
    object->SetPoints(vertexes);
    object->SetPolys(faces);

    if(nPoints == 0 || nFaces == 0){
        return false;
    }

    return true;
}

void ObjObject::printObject(QVTKWidget *widget)
{
    // Visualize
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(this->object);

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> renderer;
    if(widget->GetRenderWindow()->GetRenderers()->GetFirstRenderer() != nullptr){
        renderer = widget->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
    } else {
        renderer = vtkSmartPointer<vtkRenderer>::New();
    }

//    double *center = actor->GetCenter();
//    double *o = actor->GetOrientation();
//    double *origen = actor->GetOrigin();
    //move actor to origin point
//    vtkSmartPointer<vtkTransform> transform =
//        vtkSmartPointer<vtkTransform>::New();
//      transform->Translate(-actor->GetCenter()[0], -actor->GetCenter()[1], -actor->GetCenter()[2]);
//      actor->SetUserTransform(transform);

//      vtkActorCollection *collect = renderer->GetActors();
//      vtkActor *actor2 = collect->GetLastActor();
//      double* pos2 = actor2->GetCenter();
    renderer->AddActor(actor);
    int actors = renderer->VisibleActorCount();
    double *center2 = actor->GetCenter();

//         renderer->ResetCamera();
    renderer->SetBackground(.2, .2, .2);
    //renderer->Render();

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

