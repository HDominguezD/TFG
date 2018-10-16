#ifndef OBJOBJECT_H
#define OBJOBJECT_H
#include "AbstractClasses/object3d.h"
#include <qvector.h>
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>


class ObjObject : public Object3D
{
public:
    ObjObject();
    bool readObjectFromFile(std::string fileName);

    vtkPoints *getVertexes() const;
    void setVertexes(vtkPoints *value);

    vtkPolyData *getObject() const;
    void setObject(vtkPolyData *value);

    vtkCellArray *getFaces() const;
    void setFaces(vtkCellArray *value);

    const char* objectType();

private:
    vtkPoints* vertexes;
    vtkPolyData* object;
    vtkCellArray* faces;
};

#endif // OBJOBJECT_H
