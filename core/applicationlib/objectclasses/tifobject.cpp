#include "tifobject.h"
#include <boost/algorithm/string.hpp>
#include <vtkSmartPointer.h>
#include <vtkTIFFReader.h>
#include <vtkImageData.h>
#include <vtkImageMapper.h>
#include <vtkImageResize.h>
#include <vtkActor2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include "vtkRendererCollection.h"
#include "qfiledialog.h"

TifObject::TifObject()
{
    outputData = vtkSmartPointer<vtkImageData>::New();
    activeImage = 0;
    imageMapper = vtkSmartPointer<vtkImageMapper>::New();
}

bool TifObject::readObject()
{
    bool readed = false;
    QStringList fileNames = QFileDialog::getOpenFileNames( Q_NULLPTR, QObject::tr("Open Files"),"/path/to/file/",QObject::tr("Mesh Files (*.tiff *.tif)"));
    if(fileNames.isEmpty())
    {
        return readed;
    }

    map<string, int> *fileExtMap = new map<string, int>();
        fileExtMap->insert(pair<string, int> ("tif", 1));
        fileExtMap->insert(pair<string, int> ("tiff", 1));

    string fileName = fileNames.at(0).toStdString();

    vector<string> splitName;
    boost::split(splitName, fileName, [](char c){return c == '.';});
    string ext = splitName.at(splitName.size() - 1);

    switch(fileExtMap->find(ext)->second)
    {
        case 1 :
        {
            readed = readObjectFromFile(fileName);
            break;
        }
    }

    return readed;
}
bool TifObject::readObjectFromFile(string fileName)
{
    //Read the image
    vtkSmartPointer<vtkTIFFReader> reader = vtkSmartPointer<vtkTIFFReader>::New();
    reader->SetFileName (fileName.c_str());
    reader->Update();

    outputData = reader->GetOutput();

    return true;
}

TifObject::~TifObject()
{

}

int TifObject::getActiveImage() const
{
    return activeImage;
}

void TifObject::setActiveImage(int value)
{
    activeImage = value;
}

void TifObject::printObject(QVTKWidget *widget)
{
    // Visualize
    imageMapper->SetZSlice(activeImage);

    vtkSmartPointer<vtkActor2D> image = vtkSmartPointer<vtkActor2D>::New();
    image->SetMapper(imageMapper);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor2D(image);
    renderer->ResetCamera();
    renderer->SetBackground(.2, .2, .2);

    widget->GetRenderWindow()->GetRenderers()->RemoveAllItems();
    widget->GetRenderWindow()->AddRenderer(renderer);
    widget->GetRenderWindow()->Render();
}

const char* TifObject::objectType(){
    return "Tif";
}

void TifObject::resizeImage(int x, int y)
{
    vtkSmartPointer<vtkImageResize> resize = vtkSmartPointer<vtkImageResize>::New();
    resize->SetInputData(outputData);
    resize->SetOutputDimensions(x, y, outputData->GetDimensions()[2]);
    resize->Update();

    imageMapper->SetInputConnection(resize->GetOutputPort());
}

int *TifObject::getDimensions()
{
    return outputData->GetDimensions();
}
