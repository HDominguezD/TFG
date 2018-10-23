#ifndef VOLOBJECT_H
#define VOLOBJECT_H
#include <qvector2d.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkTIFFReader.h>

using namespace std;

class VolObject
{
public:
    virtual bool readObjectFromFile(string fileName) = 0;
    virtual bool readObjectFromFiles(QStringList fileName) = 0;
    virtual const char* objectType() = 0;
    virtual vtkSmartPointer<vtkImageData> getVolume() const = 0;
    virtual void setVolume(const vtkSmartPointer<vtkImageData> &value) = 0;
    virtual vtkSmartPointer<vtkTIFFReader> getReader() const = 0;
    virtual ~VolObject(){}
};

#endif // VOLOBJECT_H
