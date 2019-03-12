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

    vtkSmartPointer<vtkVolume> getVolume() const;
    void readTransferFunction(string fileName);

    double getMaxValue() const;
    std::array<double, 3> calculateSpacing(string name);

    double *getCenter() const;

private:
    void readObjectFromDir(QDir directory);
    vtkSmartPointer<vtkVolume> volume;
    double maxValue;
    double *center;

};

#endif // TIFVOLUMEOBJECT_H
