#include "tifvolumeobject.h"
#include "vtkImageReader.h"
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
    vtkImageReader *reader = vtkImageReader::New();
    reader->SetDataScalarTypeToUnsignedShort();

    QStringList images = directory.entryList(QStringList() << "*.tif" << "*.tiff",QDir::Files);

    if(images.size() == 0){
        return false;
    }

    vtkStringArray *imagesName = vtkStringArray::New();
    for(QString image : images){
        imagesName->InsertNextValue(directory.absolutePath().toStdString() + "/" + image.toStdString());
    }
    reader->SetFileNames(imagesName);

    vtkSmartPointer<vtkTIFFReader> header = vtkSmartPointer<vtkTIFFReader>::New();
    string fileName = reader->GetFileNames()->GetValue(0);
    header->SetFileName(fileName.c_str());
    header->Update();


    //Image data of the readed image
    vtkSmartPointer<vtkImageData> imageData = reader->GetOutput();

    //image dimensions
    int *dims = imageData->GetDimensions();

//    for(int image = 0; image < dims[2]; ++image)
//    {
//        for(int row = 0; row < dims[0]; ++row)
//        {
//            for(int col = 0; col < dims[1]; ++col)
//            {
//                ushort* pixel = static_cast<ushort*>(imageData->GetScalarPointer(row, col, image));
//                if(pixel[0] < 200)
//                {
//                    pixel[0] = 0;
//                }
//            }
//        }
//    }


    header->Update();

    int height = header->GetDataExtent()[3];
    int width = header->GetDataExtent()[1];
    int depth = static_cast<int>(directory.count() - 2);

    reader->SetDataExtent(0, width, 0, height, 0, depth);
    reader->SetDataScalarTypeToUnsignedShort();

    reader->Update();



    vtkObjectFactory::RegisterFactory(vtkRenderingOpenGL2ObjectFactory::New());
    vtkObjectFactory::RegisterFactory(vtkRenderingVolumeOpenGL2ObjectFactory::New());

    vtkFixedPointVolumeRayCastMapper *texMapper = vtkFixedPointVolumeRayCastMapper::New();
    vtkColorTransferFunction *ctf = vtkColorTransferFunction::New();
    vtkPiecewiseFunction *spwf = vtkPiecewiseFunction::New();
    vtkPiecewiseFunction *gpwf = vtkPiecewiseFunction::New();

    //Go through the visulizatin pipeline
    texMapper->SetInputConnection(reader->GetOutputPort());

    //Set the color curve for the volume
    ctf->AddHSVPoint(0, .67, .07, 1);
    ctf->AddHSVPoint(94, .67, .07, 1);
    ctf->AddHSVPoint(139, 0, 0, 0);
    ctf->AddHSVPoint(160, .28, .047, 1);
    ctf->AddHSVPoint(254, .38, .013, 1);

    //Set the opacity curve for the volume
    spwf->AddPoint(84, 0);
    spwf->AddPoint(151, .1);
    spwf->AddPoint(255, 1);

    //Set the gradient curve for the volume
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
