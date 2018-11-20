#ifndef OBJOBJECT_H
#define OBJOBJECT_H
#include "abstractclasses/object.h"
#include <vtkPoints.h>
#include <vtkPolyData.h>


class ObjObject : public Object
{
public:
    ObjObject();
    bool readObject();
    void printObject(QVTKWidget *widget);
    const char* objectType();
    ~ObjObject();

private:
    bool readObjectFromFile(std::string fileName);
    vtkSmartPointer<vtkPoints> vertexes;
    vtkSmartPointer<vtkPolyData> object;
    vtkSmartPointer<vtkCellArray> faces;
};

#endif // OBJOBJECT_H
