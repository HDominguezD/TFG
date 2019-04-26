#ifndef TIFVOLUMEOBJECT_H
#define TIFVOLUMEOBJECT_H
#include "abstractclasses/object.h"
#include <vtkVolume.h>
#include <vtkTIFFReader.h>
#include <QDir>
#include "vtkAxesActor.h"

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

    vtkSmartPointer<vtkAxesActor> getAxes() const;

    vtkSmartPointer<vtkImageData> getData() const;

    string getName() const;

    QVTKWidget *getVtkWidget() const;

    void setName(const string &value);

private:
    void readObjectFromDir(QDir directory);
    vtkSmartPointer<vtkVolume> volume;
    vtkSmartPointer<vtkImageData> data;
    vtkSmartPointer<vtkAxesActor> axes;
    double maxValue;
    string name;
    QVTKWidget *vtkWidget;

};

#endif // TIFVOLUMEOBJECT_H
