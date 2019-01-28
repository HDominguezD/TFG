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
//        int height = header->GetDataExtent()[3];
//        int width = header->GetDataExtent()[1];
//        int depth = header->GetDataExtent()[5];

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

    //image dimensions

//    reader->Update();

    //    int *dims = imageData->GetDimensions();

    //    for(int image = 0; image < dims[2]; ++image)
    //    {
    //        for(int row = 0; row < dims[0]; ++row)
    //        {
    //            for(int col = 0; col < dims[1]; ++col)
    //            {
    //                //removing pixels with value between 0 and 200 to remove some interferences
    //                ushort* pixel = static_cast<ushort*>(imageData->GetScalarPointer(row, col, image));
    //                if(pixel[0] >= 200)
    //                {
    //                    int hola = 1;
    //                }
    //            }
    //        }
    //    }

    vtkObjectFactory::RegisterFactory(vtkRenderingOpenGL2ObjectFactory::New());
    vtkObjectFactory::RegisterFactory(vtkRenderingVolumeOpenGL2ObjectFactory::New());

    vtkFixedPointVolumeRayCastMapper *texMapper = vtkFixedPointVolumeRayCastMapper::New();

    //Go through the visulizatin pipeline
//    texMapper->SetInputConnection(header->GetOutputPort());
    texMapper->SetInputData(imageData);

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

    //Set the gradient curve for the volume
    vtkPiecewiseFunction *gpwf = vtkPiecewiseFunction::New();
    gpwf->AddPoint(0, .2);
    gpwf->AddPoint(10, .2);
    gpwf->AddPoint(25, 1);


    volume->GetProperty()->SetColor(ctf);
    volume->GetProperty()->SetScalarOpacity(spwf);
    volume->GetProperty()->SetGradientOpacity(gpwf);
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
