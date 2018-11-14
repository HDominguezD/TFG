#include "objobject.h"
#include <sstream>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <vtkSmartPointer.h>
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

using namespace std;


ObjObject::ObjObject()
{
    vertexes = vtkPoints::New();
    faces = vtkCellArray::New();
    object= vtkPolyData::New();
}

bool ObjObject::readObject()
{
    QStringList fileNames = QFileDialog::getOpenFileNames( Q_NULLPTR, QObject::tr("Open File"),"/path/to/file/",QObject::tr("Mesh Files (*.obj)"));
    if(fileNames.isEmpty())
    {
        return false;
    }

    string fileName = fileNames.at(0).toStdString();

    vector<string> splitName;
    boost::split(splitName, fileName, [](char c){return c == '.';});
    string ext = splitName.at(splitName.size() - 1);

   if(ext == "obj"){
       readObjectFromFile(fileName);
   }
}

bool ObjObject::readObjectFromFile(string fileName)
{
    string line;
    ifstream input(fileName.c_str(), ifstream::out);
    int nPoints = 0;
    int nfaces = 0;
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
                nfaces++;
                break;
            };
        }
    }

    // Create a PolyData
    object->SetPoints(vertexes);
    object->SetPolys(faces);

    return true;
}

void ObjObject::printObject(QVTKWidget * widget)
{
    // Visualize
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(this->object);

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(.2, .2, .2);

    widget->GetRenderWindow()->GetRenderers()->RemoveAllItems();
    widget->GetRenderWindow()->AddRenderer(renderer);
    widget->GetRenderWindow()->Render();
}

const char* ObjObject::objectType()
{
    return "obj";
}

