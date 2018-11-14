#ifndef OBJECT_H
#define OBJECT_H
#include <qvector2d.h>
#include <vtkSmartPointer.h>
#include <vtkImageMapper.h>
#include <vtkRenderer.h>
#include <QVTKWidget.h>

using namespace std;

class Object
{
public:
    virtual bool readObject() = 0;
    virtual const char* objectType() = 0;
    virtual void printObject(QVTKWidget * widget) = 0;
    virtual ~Object(){}
};

#endif // OBJECT2D_H
