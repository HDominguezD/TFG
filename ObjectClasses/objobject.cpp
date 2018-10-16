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

using namespace std;

ObjObject::ObjObject()
{
    vertexes = vtkPoints::New();
    faces = vtkCellArray::New();
    object= vtkPolyData::New();


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

vtkPoints *ObjObject::getVertexes() const
{
    return vertexes;
}

void ObjObject::setVertexes(vtkPoints *value)
{
    vertexes = value;
}

vtkPolyData *ObjObject::getObject() const
{
    return object;
}

void ObjObject::setObject(vtkPolyData *value)
{
    object = value;
}

vtkCellArray *ObjObject::getFaces() const
{
    return faces;
}

void ObjObject::setFaces(vtkCellArray *value)
{
    faces = value;
}

const char* ObjObject::objectType()
{
    return "obj";
}

