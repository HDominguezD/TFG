#include "tifvolumeobject.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkRenderWindow.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkTIFFReader.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <qstringlist.h>
#include <vtkUnsignedShortArray.h>
#include <vtkPointData.h>
#include <vtkIdTypeArray.h>
#include <vtkAbstractArray.h>
#include <vtkDataSetMapper.h>


TifVolumeObject::TifVolumeObject()
{
    volume = vtkSmartPointer<vtkImageData>::New();
    reader = vtkSmartPointer<vtkTIFFReader>::New();


}

bool TifVolumeObject::readObjectFromFile(string fileName)
{

}
bool TifVolumeObject::readObjectFromFiles(QStringList fileNames)
{
    reader->SetFileName (fileNames.at(0).toStdString().c_str());
    reader->Update();

    vtkSmartPointer<vtkImageData> image = reader->GetOutput();

    volume = vtkSmartPointer<vtkImageData>::New();
    volume->SetExtent(0, image->GetExtent()[1], 0, image->GetExtent()[3], 0, fileNames.size() - 1);

    vtkIdType ncells = volume->GetNumberOfCells();
    vtkIdType npoints = volume->GetNumberOfPoints();

    vtkUnsignedShortArray *array = vtkUnsignedShortArray::New();
    array->SetNumberOfValues(npoints);

    for(int i = 0; i < fileNames.size(); i++){
        reader->SetFileName(fileNames.at(i).toStdString().c_str());
        reader->Update();
        image = reader->GetOutput();

        vtkDataArray *vals = image->GetPointData()->GetArray("Tiff Scalars");
        vtkIdType offset = i* fileNames.size();
        vtkIdType nTupples = vals->GetNumberOfTuples();
        for(vtkIdType j = 0; j < vals->GetNumberOfTuples(); j++){
            bool *bol = new bool(true);
            array->SetValue(offset + j,vals->GetVariantValue(j).ToShort(bol));
        }
    }
    volume->GetPointData()->AddArray(array);

    return true;
}

const char *TifVolumeObject::objectType()
{

}

vtkSmartPointer<vtkImageData> TifVolumeObject::getVolume() const
{
    return volume;
}

void TifVolumeObject::setVolume(const vtkSmartPointer<vtkImageData> &value)
{
    volume = value;
}

vtkSmartPointer<vtkTIFFReader> TifVolumeObject::getReader() const
{
    return reader;
}
