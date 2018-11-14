#ifndef OBJOBJECT_H
#define OBJOBJECT_H
#include "abstractclasses/object.h"
#include <qvector.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>


class ObjObject : public Object
{
public:
    ObjObject();
    bool readObject();
    void printObject(QVTKWidget * widget);
    const char* objectType();

private:
    bool readObjectFromFile(std::string fileName);
    vtkPoints* vertexes;
    vtkPolyData* object;
    vtkCellArray* faces;
};

#endif // OBJOBJECT_H
