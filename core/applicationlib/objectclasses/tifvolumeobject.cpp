#include "tifvolumeobject.h"
#include "vtkImageReader2.h"
#include "vtkStringArray.h"
#include "QDir"
#include "vtkObjectFactory.h"
#include "vtkRenderingOpenGL2ObjectFactory.h"
#include "vtkRenderingVolumeOpenGL2ObjectFactory.h"
#include "vtkFixedPointVolumeRayCastMapper.h"
#include "vtkVolume.h"
#include "vtkColorTransferFunction.h"
#include "vtkPiecewiseFunction.h"
#include "vtkVolumeProperty.h"
#include "qfiledialog.h"
#include "vtkRenderWindow.h"
#include "vtkRendererCollection.h"
#include "vtkTransform.h"
#include "vtkImageData.h"
#include <boost/algorithm/string.hpp>

TifVolumeObject::TifVolumeObject()
{
    volume = vtkSmartPointer<vtkVolume>::New();
}

bool TifVolumeObject::readObject()
{
    QDir directory = QFileDialog::getExistingDirectory(Q_NULLPTR, QObject::tr("select directory"));
    if(!directory.exists())
    {
        return false;
    }

    QStringList images = directory.entryList(QStringList() << "*.tif" << "*.tiff",QDir::Files);

    if(images.size() == 0){
        return false;
    }

    vtkStringArray *imagesName = vtkStringArray::New();
    for(QString image : images){
        imagesName->InsertNextValue(directory.absolutePath().toStdString() + "/" + image.toStdString());
    }

    vtkSmartPointer<vtkTIFFReader> header = vtkSmartPointer<vtkTIFFReader>::New();
    vtkImageReader2 *reader = vtkImageReader2::New();

    //Image data of the readed image
    vtkSmartPointer<vtkImageData> imageData = vtkSmartPointer<vtkImageData>::New();

    if(imagesName->GetSize() > 1)
    {
        reader->SetFileNames(imagesName);

        string fileName = imagesName->GetValue(0);
        header->SetFileName(fileName.c_str());
        header->Update();

        int *data = header->GetDataExtent();

        reader->SetDataExtent(data);
        int type = header->GetDataScalarType();
        reader->SetDataScalarType(type);
        reader->Update();

        imageData = reader->GetOutput();
    } else
    {
        string fileName = imagesName->GetValue(0);
        header->SetFileName(fileName.c_str());
        header->Update();

        imageData = header->GetOutput();
    }

    vtkObjectFactory::RegisterFactory(vtkRenderingOpenGL2ObjectFactory::New());
    vtkObjectFactory::RegisterFactory(vtkRenderingVolumeOpenGL2ObjectFactory::New());

    vtkFixedPointVolumeRayCastMapper *texMapper = vtkFixedPointVolumeRayCastMapper::New();

    //Go through the visulizatin pipeline

    texMapper->SetInputData(imageData);

    QStringList transferFunction = directory.entryList(QStringList() << "*.trans",QDir::Files);

    if(transferFunction.isEmpty()){
        //Set the color curve for the volume
        //first parameter is the value of the pixel and the rest the rgb color value
        //the pixel will have when it has the first value
        vtkColorTransferFunction *ctf = vtkColorTransferFunction::New();
        ctf->AddRGBPoint(0, .91f, .7f, .61f);
        ctf->AddRGBPoint(20, .91f, .7f, .61f);
        ctf->AddRGBPoint(100, 1.0f, 1.0f, .85f);
        ctf->AddRGBPoint(200, 1.0f, 1.0f, .85f);

        //Set the opacity curve for the volume
        //first parameter is the value of the pixel and the second the opacity value
        //the pixel will have when it has the first value
        vtkPiecewiseFunction *spwf = vtkPiecewiseFunction::New();
        spwf->AddPoint(100, 0);
        spwf->AddPoint(140, .5);
        spwf->AddPoint(200, 1);

        // The gradient opacity function is used to decrease the opacity
        // in the "flat" regions of the volume while maintaining the opacity
        // at the boundaries between tissue types.  The gradient is measured
        // as the amount by which the intensity changes over unit distance.
        // For most medical data, the unit distance is 1mm.
        vtkPiecewiseFunction *gpwf = vtkPiecewiseFunction::New();
        gpwf->AddPoint(0, .2);
        gpwf->AddPoint(90, .5);
        gpwf->AddPoint(100, 1);


        vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
        volumeProperty->SetColor(ctf);
        volumeProperty->SetScalarOpacity(spwf);
        volumeProperty->SetGradientOpacity(gpwf);
        volumeProperty->SetInterpolationTypeToLinear();
        volumeProperty->ShadeOn();


        //Ambient especificates how the material reacts to global litghning
        volumeProperty->SetAmbient(0.6);
        //diffuse determines the average path of light in the material
        volumeProperty->SetDiffuse(0.5);
        //Specular determines how the light is reflected in the material
        volumeProperty->SetSpecular(0.4);

        volume->SetProperty(volumeProperty);
    } else {
        readTransferFunction(directory.absolutePath().toStdString() + "/" + transferFunction.at(0).toStdString());
    }

    volume->SetMapper(texMapper);

    return true;
}

void TifVolumeObject::printObject(QVTKWidget *widget)
{
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(.2, .2, .2);

    vtkSmartPointer<vtkTransform> transform =
        vtkSmartPointer<vtkTransform>::New();
      transform->Translate(-this->volume->GetCenter()[0], -this->volume->GetCenter()[1], -this->volume->GetCenter()[2]);
      volume->SetUserTransform(transform);

    renderer->AddVolume(this->volume);

    widget->GetRenderWindow()->GetRenderers()->RemoveAllItems();
    widget->GetRenderWindow()->AddRenderer(renderer);
    widget->GetRenderWindow()->Render();
}

const char *TifVolumeObject::objectType()
{
    return "TifVolume";
}

TifVolumeObject::~TifVolumeObject()
{

}

vtkSmartPointer<vtkVolume> TifVolumeObject::getVolume() const
{
    return volume;
}

void TifVolumeObject::readTransferFunction(string fileName)
{
    string line;
    ifstream input(fileName.c_str(), ifstream::out);

    static map<string, int> s_mapStringValues;
        s_mapStringValues.insert(pair<string, int>(string("c "), 1));
        s_mapStringValues.insert(pair<string, int>(string("s "), 2));
        s_mapStringValues.insert(pair<string, int>(string("g "), 3));

    vtkColorTransferFunction *ctf = vtkColorTransferFunction::New();
    vtkPiecewiseFunction *gpwf = vtkPiecewiseFunction::New();
    vtkPiecewiseFunction *spwf = vtkPiecewiseFunction::New();

    while (getline(input, line))
    {
        string beginning = line.substr(0, 2);
        vector<string> results;
        boost::split(results, line, [](char c){return c == ' ';});

        switch (s_mapStringValues.find(beginning)->second)
        {
            case 1:
            {
                ctf->AddRGBPoint(stof(results.at(1)), stof(results.at(2)), stof(results.at(3)), stof(results.at(4)));
                break;
            }
            case 2:
            {
                spwf->AddPoint(stof(results.at(1)), stof(results.at(2)));
                break;
            }
            case 3:
            {
                gpwf->AddPoint(stof(results.at(1)), stof(results.at(2)));
                break;
            };
        }
    }
    vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
    volumeProperty->SetColor(ctf);
    volumeProperty->SetScalarOpacity(spwf);
    volumeProperty->SetGradientOpacity(gpwf);
    //volumeProperty->SetInterpolationTypeToLinear();
    volumeProperty->ShadeOn();

    int j = volumeProperty->GetScalarOpacity()->GetSize();
    //Ambient especificates how the material reacts to global litghning
    volumeProperty->SetAmbient(0.6);
    //diffuse determines the average path of light in the material
    volumeProperty->SetDiffuse(0.5);
    //Specular determines how the light is reflected in the material
    volumeProperty->SetSpecular(0.4);

    volume->SetProperty(volumeProperty);
}
