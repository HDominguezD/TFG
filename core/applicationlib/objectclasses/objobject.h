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

    double *getCenter() const;

    vtkSmartPointer<vtkActor> getActor() const;

private:
    bool readObjectFromFile(std::string fileName);
    vtkSmartPointer<vtkActor> actor;
    double *center;
};

#endif // OBJOBJECT_H
