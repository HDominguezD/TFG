#ifndef OBJECT3D_H
#define OBJECT3D_H
#include <qvector.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>

using namespace std;

class Object3D
{
public:
    virtual bool readObjectFromFile(string fileName) = 0;

    virtual vtkPoints *getVertexes() const = 0;
    virtual void setVertexes(vtkPoints *value) = 0;

    virtual vtkPolyData *getObject() const = 0;
    virtual void setObject(vtkPolyData *value) = 0;

    virtual vtkCellArray *getFaces() const = 0;
    virtual void setFaces(vtkCellArray *value) = 0;

    virtual const char* objectType() = 0;
    virtual ~Object3D(){}
};

#endif // OBJECT3D_H
