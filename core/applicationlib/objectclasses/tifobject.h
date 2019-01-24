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
    void resizeImage(int x, int y);
    int * getDimensions();
    bool readObjectFromFile(std::string fileName);
    ~TifObject();

    int getActiveImage() const;
    void setActiveImage(int value);

private:
    vtkSmartPointer<vtkImageData> outputData;
    int activeImage;
    vtkSmartPointer<vtkImageMapper> imageMapper;
};

#endif // TIFOBJECT_H
