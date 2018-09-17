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
    vertexes = new QVector<vtkSmartPointer<vtkPoints>>();
    faces = new QVector<vtkSmartPointer<vtkPolyData>>();
}

bool ObjObject::readObjectFromFile(std::string fileName)
{
    std::string line;
    std::ifstream input(fileName.c_str(), std::ifstream::out);
    while (std::getline(input, line))
    {
        switch (line[0])
        {
            case 'v':
            {
                std::vector<std::string> results;
                boost::split(results, line, [](char c){return c == ' ';});
                vtkSmartPointer<vtkPoints> vertex = vtkSmartPointer<vtkPoints>::New();
                vertex->InsertNextPoint(std::stof(results.at(1)), std::stof(results.at(2)), std::stof(results.at(3)));
                this->vertexes->append(vertex);
                break;
            }
            case 'f':
            {
                std::vector<std::string> results;
                boost::split(results, line, [](char c){return c == ' ';});

                // Create the polygon
                vtkSmartPointer<vtkPolygon> polygon = vtkSmartPointer<vtkPolygon>::New();
                polygon->GetPointIds()->SetNumberOfIds(results.size() - 1); //make a quad

                vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
                for(int i = 1; i < results.size(); i++)
                {
                    points->InsertNextPoint(this->vertexes->at(std::stoi(results[i]) - 1)->GetPoint(0));
                    polygon->GetPointIds()->SetId(i - 1, i - 1);
                }

                // Add the polygon to a list of polygons
                vtkSmartPointer<vtkCellArray> polygons = vtkSmartPointer<vtkCellArray>::New();
                polygons->InsertNextCell(polygon);

                // Create a PolyData
                vtkSmartPointer<vtkPolyData> polygonPolyData =
                vtkSmartPointer<vtkPolyData>::New();
                polygonPolyData->SetPoints(points);
                polygonPolyData->SetPolys(polygons);
                faces->append(polygonPolyData);
                break;
            };
        }
    }
    return true;
}

QVector<vtkSmartPointer<vtkPoints> > *ObjObject::getVertexes() const
{
    return vertexes;
}

void ObjObject::setVertexes(QVector<vtkSmartPointer<vtkPoints> > *value)
{
    vertexes = value;
}

QVector<vtkSmartPointer<vtkPolyData> > *ObjObject::getFaces() const
{
    return faces;
}

void ObjObject::setFaces(QVector<vtkSmartPointer<vtkPolyData> > *value)
{
    faces = value;
}

