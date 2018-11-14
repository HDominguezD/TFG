#ifndef TIFOBJECT_H
#define TIFOBJECT_H
#include "AbstractClasses/object.h"
#include "vtkSmartPointer.h"
#include "vtkImageStack.h"


class TifObject : public Object
{
public:
    TifObject();
    bool readObject();
    void printObject(QVTKWidget * widget);
    const char* objectType();

private:
    bool readObjectFromFile(std::string fileName);
    vtkSmartPointer<vtkImageMapper> imageMapper;
    vtkSmartPointer<vtkImageData> outputData;
};

#endif // TIFOBJECT_H
