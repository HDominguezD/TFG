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

    string getName() const;

    vtkSmartPointer<vtkActor> getActor() const;

    vtkSmartPointer<vtkAxesActor> getAxes() const;

    QVTKWidget *getVtkWidget() const;

    void setName(const string &value);

private:
    bool readObjectFromFile(std::string fileName);
    vtkSmartPointer<vtkActor> actor;
    vtkSmartPointer<vtkAxesActor> axes;
    string name;
    QVTKWidget *vtkWidget;
};

#endif // OBJOBJECT_H
