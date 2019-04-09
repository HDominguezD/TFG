#ifndef OBJOBJECT_H
#define OBJOBJECT_H
#include "abstractclasses/object.h"
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkActor.h>
#include "vtkAxesActor.h"


class ObjObject : public Object
{
public:
    ObjObject();
    bool readObject();
    void printObject(QVTKWidget *widget);
    const char* objectType();
    ~ObjObject();

    vtkSmartPointer<vtkActor> getActor() const;

    vtkSmartPointer<vtkAxesActor> getAxes() const;

private:
    bool readObjectFromFile(std::string fileName);
    vtkSmartPointer<vtkActor> actor;
    vtkSmartPointer<vtkAxesActor> axes;
};

#endif // OBJOBJECT_H
