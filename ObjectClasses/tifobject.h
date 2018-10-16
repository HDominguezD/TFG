#ifndef TIFOBJECT_H
#define TIFOBJECT_H
#include "AbstractClasses/object2d.h"
#include "vtkSmartPointer.h"
#include "vtkImageMapper.h"


class TifObject : public Object2D
{
public:
    TifObject();
    bool readObjectFromFile(std::string fileName);

    vtkSmartPointer<vtkImageMapper> getImageMapper() const;
    void setImageMapper(const vtkSmartPointer<vtkImageMapper> &value);

    vtkSmartPointer<vtkImageData> getOutputData() const;

private:
    vtkSmartPointer<vtkImageMapper> imageMapper;
    vtkSmartPointer<vtkImageData> outputData;
};

#endif // TIFOBJECT_H
