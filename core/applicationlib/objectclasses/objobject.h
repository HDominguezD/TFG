#ifndef OBJOBJECT_H
#define OBJOBJECT_H
#include "abstractclasses/object.h"
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkActor.h>


class ObjObject : public Object
{
public:
    ObjObject();
    bool readObject();
    void printObject(QVTKWidget *widget);
    const char* objectType();
    ~ObjObject();

    vtkSmartPointer<vtkActor> getActor() const;

private:
    bool readObjectFromFile(std::string fileName);
    vtkSmartPointer<vtkActor> actor;
};

#endif // OBJOBJECT_H
