#ifndef TIFOBJECT_H
#define TIFOBJECT_H
#include "abstractclasses/object.h"
#include <vtkActor2D.h>
#include <vtkImageMapper.h>
#include "core.h"
#include "QVTKWidget.h"


class TifObject : public Object
{
public:
    TifObject();
    bool readObject();
    void printObject(QVTKWidget *widget);
    const char* objectType();
    void resizeImage(QVTKWidget *widget);
    int * getDimensions();
    bool readObjectFromFile(std::string fileName);
    ~TifObject();

    int getActiveImage() const;
    void setActiveImage(int value);

private:
    vtkSmartPointer<vtkActor2D> actor2D;
    vtkSmartPointer<vtkImageData> outputData;
    vtkSmartPointer<vtkImageMapper> imageMapper;
    int activeImage;
};

#endif // TIFOBJECT_H
