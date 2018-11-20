#ifndef TIFOBJECT_H
#define TIFOBJECT_H
#include "abstractclasses/object.h"
#include <vtkImageMapper.h>
#include "core.h"


class TifObject : public Object
{
public:
    TifObject();
    bool readObject();
    void printObject(QVTKWidget *widget);
    const char* objectType();
    bool readObjectFromFile(std::string fileName);
    ~TifObject();

private:
    vtkSmartPointer<vtkImageMapper> imageMapper;
    vtkSmartPointer<vtkImageData> outputData;
};

#endif // TIFOBJECT_H
