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

ObjObject::ObjObject()
{
    vertexes = vtkPoints::New();
    faces = vtkCellArray::New();
    object= vtkPolyData::New();


}

bool ObjObject::readObjectFromFile(std::string fileName)
{
    std::string line;
    std::ifstream input(fileName.c_str(), std::ifstream::out);
    int nPoints = 0;
    while (std::getline(input, line))
    {
        switch (line[0])
        {
            case 'v':
            {
                std::vector<std::string> results;
                boost::split(results, line, [](char c){return c == ' ';});
                vertexes->InsertPoint(nPoints, std::stod(results.at(1)), std::stod(results.at(2)), std::stod(results.at(3)));

                nPoints++;
                break;
            }
            case 'f':
            {
                std::vector<std::string> results;
                boost::split(results, line, [](char c){return c == ' ';});


                vtkIdList *pts = vtkIdList::New();

                for(ulong i = 1; i < results.size(); i++)
                {
                    pts->InsertId(static_cast<long long> (i-1), std::stoi(results.at(i)) -1);
                    long long k = pts->GetId(static_cast<long long>(i-1));
                    k++;
                }


                // Add the polygon to a list of polygons
                faces->InsertNextCell(pts);

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

