#ifndef TIFVOLUMEOBJECT_H
#define TIFVOLUMEOBJECT_H
#include "AbstractClasses/volobject.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkTIFFReader.h>

class TifVolumeObject : public VolObject
{
public:
    TifVolumeObject();
    bool readObjectFromFile(string fileName);
    bool readObjectFromFiles(QStringList fileNames);

    const char* objectType();

    vtkSmartPointer<vtkImageData> getVolume() const;
    void setVolume(const vtkSmartPointer<vtkImageData> &value);

    vtkSmartPointer<vtkTIFFReader> getReader() const;

private:
    vtkSmartPointer<vtkImageData> volume;
    vtkSmartPointer<vtkTIFFReader> reader;

};

#endif // TIFVOLUMEOBJECT_H
