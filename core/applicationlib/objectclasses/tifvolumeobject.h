#ifndef TIFVOLUMEOBJECT_H
#define TIFVOLUMEOBJECT_H
#include "abstractclasses/object.h"
#include <vtkVolume.h>
#include <vtkTIFFReader.h>
#include <QDir>

class TifVolumeObject : public Object
{
public:
    TifVolumeObject();
    bool readObject();
    void printObject(QVTKWidget *widget);
    const char* objectType();
    ~TifVolumeObject();

private:
    void readObjectFromDir(QDir directory);
    vtkSmartPointer<vtkVolume> volume;

};

#endif // TIFVOLUMEOBJECT_H
