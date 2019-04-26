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
    activeImage = 0;
    actor2D = vtkSmartPointer<vtkActor2D>::New();
    outputData = vtkSmartPointer<vtkImageData>::New();
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

    imageMapper->SetInputData(outputData);
    imageMapper->SetZSlice(activeImage);

    actor2D->SetMapper(imageMapper);

    vector<string> splitName;
    boost::split(splitName, fileName, [](char c){return c == '/';});
    name = splitName.at(splitName.size() - 1);

    return true;
}

TifObject::~TifObject()
{
    actor2D->VisibilityOff();
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
    imageMapper->SetZSlice(activeImage);
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor2D(actor2D);
    renderer->ResetCamera();
    renderer->SetBackground(.2, .2, .2);

    widget->GetRenderWindow()->GetRenderers()->RemoveAllItems();
    widget->GetRenderWindow()->AddRenderer(renderer);
    widget->GetRenderWindow()->Render();
}

const char* TifObject::objectType(){
    return "Tif";
}

void TifObject::resizeImage(QVTKWidget *widget)
{
    int x = widget->width();
    int y = widget->height();
    int *dims = outputData->GetDimensions();
    int resizeX = 0;
    int resizeY = 0;

    if((x / dims[0]) < (y / dims[1])){
        resizeX = x;
        resizeY = (dims[1]) / ((float)dims[0] / (float)x);
    } else {
        resizeY = y;
        resizeX = (dims[0]) / ((float)dims[1] / (float)y);
    }


    vtkSmartPointer<vtkImageResize> resize = vtkSmartPointer<vtkImageResize>::New();
    resize->SetInputData(outputData);
    resize->SetOutputDimensions(resizeX, resizeY, outputData->GetDimensions()[2]);
    resize->Update();

    actor2D->GetMapper()->SetInputConnection(resize->GetOutputPort());
    QSize *size = new QSize(resizeX, resizeY);
    widget->setFixedSize(*size);
}

int *TifObject::getDimensions()
{
    return outputData->GetDimensions();
}

string TifObject::getName() const
{
    return name;
}

QVTKWidget *TifObject::getVtkWidget() const
{
    return vtkWidget;
}

vtkSmartPointer<vtkActor2D> TifObject::getActor2D() const
{
    return actor2D;
}

void TifObject::setName(const string &value)
{
    name = value;
}
