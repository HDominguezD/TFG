#ifndef TIFOBJECT_H
#define TIFOBJECT_H
#include "abstractclasses/object.h"
#include "vtkSmartPointer.h"
#include "vtkImageStack.h"
#include "core.h"


class TifObject : public Object
{
public:
    TifObject();
    bool readObject();
    void printObject(QVTKWidget * widget);
    const char* objectType();
    bool readObjectFromFile(std::string fileName);

private:
    vtkSmartPointer<vtkImageMapper> imageMapper;
    vtkSmartPointer<vtkImageData> outputData;
};

#endif // TIFOBJECT_H
