#ifndef OBJECT2D_H
#define OBJECT2D_H
#include <qvector2d.h>
#include <vtkSmartPointer.h>
#include <vtkImageMapper.h>

using namespace std;

class Object2D
{
public:
    virtual bool readObjectFromFile(string fileName) = 0;
    virtual vtkSmartPointer<vtkImageMapper> getImageMapper() const = 0;
    virtual void setImageMapper(const vtkSmartPointer<vtkImageMapper> &value) = 0;
    virtual vtkSmartPointer<vtkImageData> getOutputData() const = 0;
    virtual const char* objectType() = 0;
    virtual ~Object2D(){}
};

#endif // OBJECT2D_H
