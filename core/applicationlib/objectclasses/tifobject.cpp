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
#include <vtkImageResize.h>
#include <vtkActor2D.h>
#include "vtkRenderWindow.h"
#include "vtkRendererCollection.h"
#include "qfiledialog.h"
#include <boost/algorithm/string.hpp>

TifObject::TifObject()
{
    imageMapper = vtkSmartPointer<vtkImageMapper>::New();
    outputData = vtkSmartPointer<vtkImageData>::New();
}

bool TifObject::readObject()
{
    QStringList fileNames = QFileDialog::getOpenFileNames( Q_NULLPTR, QObject::tr("Open Files"),"/path/to/file/",QObject::tr("Mesh Files (*.tiff *.tif)"));
    if(fileNames.isEmpty())
    {
        return false;
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
            readObjectFromFile(fileName);
            break;
        }
    }
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

void TifObject::printObject(QVTKWidget * widget)
{
    // Visualize
    vtkSmartPointer<vtkImageResize> resize = vtkSmartPointer<vtkImageResize>::New();
    resize->SetInputData(this->outputData);
    resize->SetOutputDimensions(widget->width(), widget->height(), 1);
    resize->Update();

    vtkSmartPointer<vtkImageMapper> imageMapper = this->imageMapper;
    imageMapper->SetInputConnection(resize->GetOutputPort());

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
