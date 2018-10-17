#include "tifobject.h"
#include <vtkSmartPointer.h>
#include <vtkTIFFReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkTIFFReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageMapper.h>
#include <vtkImageData.h>

TifObject::TifObject()
{
    imageMapper = vtkSmartPointer<vtkImageMapper>::New();
    outputData = vtkSmartPointer<vtkImageData>::New();
}

bool TifObject::readObjectFromFile(string fileName)
{
    //Read the image
    vtkSmartPointer<vtkTIFFReader> reader = vtkSmartPointer<vtkTIFFReader>::New();
    reader->SetFileName (fileName.c_str());
    reader->Update();
    imageMapper = vtkSmartPointer<vtkImageMapper>::New();
    imageMapper->SetInputData(reader->GetOutput());
    outputData = reader->GetOutput();

    return true;
}

vtkSmartPointer<vtkImageMapper> TifObject::getImageMapper() const
{
    return imageMapper;
}

void TifObject::setImageMapper(const vtkSmartPointer<vtkImageMapper> &value)
{
    imageMapper = value;
}

vtkSmartPointer<vtkImageData> TifObject::getOutputData() const
{
    return outputData;
}

const char* TifObject::objectType(){
    return "tif";
}
