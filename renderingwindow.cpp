#include "renderingwindow.h"
#include "ui_renderingwindow.h"
#include "ObjectClasses/AbstractClasses/volobject.h"
#include "ObjectClasses/tifvolumeobject.h"
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPolygon.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCamera.h>
#include <qwindow.h>
#include <qmainwindow.h>
#include <qfiledialog.h>
#include <boost/algorithm/string.hpp>
#include <map>
#include <vtkImageActor.h>
#include <vtkImageMapper.h>
#include <vtkActor2D.h>
#include <vtkImageResize.h>
#include <vtkImageData.h>
#include <QVTKOpenGLWidget.h>
#include <vtkSphereSource.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <QVTKInteractor.h>
#include <vtkRendererCollection.h>
#include <vtkDataSetMapper.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkSphere.h>
#include <vtkSampleFunction.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVolumeProperty.h>
#include <vtkCamera.h>
#include <vtkImageShiftScale.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <vtkXMLImageDataReader.h>
#include "vtkVolume.h"
#include "vtkVolumeProperty.h"
#include "vtkXMLImageDataReader.h"
#include "vtkSmartVolumeMapper.h"
#include "vtkRenderingOpenGL2ObjectFactory.h"
#include "vtkRenderingVolumeOpenGL2ObjectFactory.h"
#include "vtkCamera.h"
#include "vtkTIFFReader.h"
#include "vtkImageSliceMapper.h"
#include "vtkImageProperty.h"
#include "vtkImageStack.h"
#include "vtkFixedPointVolumeRayCastMapper.h"
#include "vtkImageReader.h"
#include "vtkStringArray.h"
#include "vtkMetaImageReader.h"
#include "vtkInteractorStyleImage.h"
using namespace std;

RenderingWindow::RenderingWindow(QWidget *parent, Core *core) :
    QMainWindow(parent),
    ui(new Ui::RenderingWindow)
{
    ui->setupUi(this);
    showOnlyToolBar();
    this->core = core;
}

RenderingWindow::~RenderingWindow()
{
    delete ui;
    delete core;
}

void RenderingWindow::printObjObject(Object3D* obj)
{
    // Visualize
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(obj->getObject());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(.2, .2, .2);

    ui->qvtkWidget->GetRenderWindow()->GetRenderers()->RemoveAllItems();
    ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
    ui->qvtkWidget->GetRenderWindow()->Render();
}

void RenderingWindow::printTifObject(Object2D* obj)
{
    // Visualize
    vtkSmartPointer<vtkImageResize> resize = vtkSmartPointer<vtkImageResize>::New();
    resize->SetInputData(obj->getOutputData());
    resize->SetOutputDimensions(ui->qvtkWidget->width(), ui->qvtkWidget->height(), 1);
    resize->Update();

    vtkSmartPointer<vtkImageMapper> imageMapper = obj->getImageMapper();
    imageMapper->SetInputConnection(resize->GetOutputPort());

    vtkSmartPointer<vtkActor2D> image = vtkSmartPointer<vtkActor2D>::New();
    image->SetMapper(imageMapper);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor2D(image);
    renderer->ResetCamera();
    renderer->SetBackground(.2, .2, .2);

    ui->qvtkWidget->GetRenderWindow()->GetRenderers()->RemoveAllItems();
    ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
    ui->qvtkWidget->GetRenderWindow()->Render();
}

void RenderingWindow::printObjects3D()
{

    for(Object3D *obj : *core->getObjects3D())
    {
        if(strcmp(obj->objectType(), "obj") == 0)
        {
            printObjObject(obj);
        }
    }
}

void RenderingWindow::on_actionopen_file_triggered()
{
    QStringList fileNames = QFileDialog::getOpenFileNames( Q_NULLPTR, QObject::tr("Open File"),"/path/to/file/",QObject::tr("Mesh Files (*.obj *.tiff *.tif)"));
    if(fileNames.isEmpty())
    {
        return;
    }

    ui->horizontalSlider->hide();
    ui->centralwidget->show();

    string fileName = fileNames.at(0).toStdString();

    vector<string> splitName;
    boost::split(splitName, fileName, [](char c){return c == '.';});
    string ext = splitName.at(splitName.size() - 1);
    map<string, int> *fileExtMap = new map<string, int>();
        fileExtMap->insert(pair<string, int> ("obj", 1));
        fileExtMap->insert(pair<string, int> ("tif", 2));
        fileExtMap->insert(pair<string, int> ("tiff", 2));

    switch(fileExtMap->find(ext)->second){
        case 1 :
        {
            Object3D *object = new ObjObject();
            if(object != nullptr){
                object->readObjectFromFile(fileName);
                core->addObject3D(object);
                this->printObjects3D();
            }
            break;
        }
        case 2 :
        {
            Object2D *object = new TifObject();
            if(object != nullptr){
                object->readObjectFromFile(fileName);
                core->addObject2D(object);
                printTifObject(object);
            }
            break;
        }
    }
}

void RenderingWindow::on_actionopen_stack_of_files_triggered()
{
    QStringList fileNames = QFileDialog::getOpenFileNames( Q_NULLPTR, QObject::tr("Open Files"),"/path/to/file/",QObject::tr("Mesh Files (*.tiff *.tif)"));
    if(fileNames.isEmpty())
    {
        return;
    }

    ui->centralwidget->show();
    ui->horizontalSlider->show();

    for(QString name : fileNames)
    {
        string fileName = name.toStdString();

        vector<string> splitName;
        boost::split(splitName, fileName, [](char c){return c == '.';});
        string ext = splitName.at(splitName.size() - 1);

        map<string, int> *fileExtMap = new map<string, int>();
            fileExtMap->insert(pair<string, int> ("tif", 1));
            fileExtMap->insert(pair<string, int> ("tiff", 1));

        switch(fileExtMap->find(ext)->second)
        {
            case 1 :
            {
                Object2D *object = new TifObject();
                if(object != nullptr){
                    object->readObjectFromFile(fileName);
                    core->addObject2D(object);
                }
                break;
            }
        }
    }
    initializateSlider();
}

void RenderingWindow::on_horizontalSlider_valueChanged(int value)
{
    printTifObject(core->getObjects2D()->at(value));
}

void RenderingWindow::initializateSlider()
{
    if(core->getObjects2D() != nullptr)
    {
        ui->horizontalSlider->setMaximum(core->getObjects2D()->size() - 1);
        ui->horizontalSlider->setMinimum(0);
        ui->horizontalSlider->setValue(0);

        printTifObject(core->getObjects2D()->at(0));
    }
}

void RenderingWindow::showOnlyToolBar()
{
    QRect geometry = this->geometry();
    geometry.setHeight(20);
    this->setGeometry(geometry);

    ui->centralwidget->hide();
    ui->horizontalSlider->hide();
}

//void RenderingWindow::on_actionopen_tif_Volume_triggered()
//{
//    QStringList fileNames = QFileDialog::getOpenFileNames( Q_NULLPTR, QObject::tr("Open Files"),"/path/to/file/",QObject::tr("Mesh Files (*.tiff *.tif)"));
//    if(fileNames.isEmpty())
//    {
//        return;
//    }

//    ui->centralwidget->show();
//    VolObject *obj = new TifVolumeObject();
//    obj->readObjectFromFiles(fileNames);

//    vtkObjectFactory::RegisterFactory(vtkRenderingOpenGL2ObjectFactory::New());
//    vtkObjectFactory::RegisterFactory(vtkRenderingVolumeOpenGL2ObjectFactory::New());

//    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
//    mapper->SetInputData(obj->getVolume());

//    vtkSmartPointer<vtkActor> volume =vtkSmartPointer<vtkActor>::New();
//    volume->SetMapper(mapper);

//    vtkSmartPointer<vtkRenderer> renderer =
//      vtkSmartPointer<vtkRenderer>::New();

//    renderer->AddViewProp(volume);

//    ui->qvtkWidget->GetRenderWindow()->GetRenderers()->RemoveAllItems();
//    ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
//    ui->qvtkWidget->GetRenderWindow()->Render();

//}



//void RenderingWindow::on_actionopen_tif_Volume_triggered()
//{
//    QStringList fileNames = QFileDialog::getOpenFileNames( Q_NULLPTR, QObject::tr("Open Files"),"/path/to/file/",QObject::tr("Mesh Files (*.tiff *.tif)"));
//    if(fileNames.isEmpty())
//    {
//        return;
//    }
//    ui->centralwidget->show();

//    vtkSmartPointer<vtkTIFFReader> reader = vtkSmartPointer<vtkTIFFReader>::New();
//    // Stack
//    vtkSmartPointer<vtkImageStack> imageStack = vtkSmartPointer<vtkImageStack>::New();

//    for(QString name : fileNames){
//        reader->SetFileName (name.toStdString().c_str());
//        reader->Update();
//        vtkSmartPointer<vtkImageData> image = reader->GetOutput();
//        vtkSmartPointer<vtkImageSliceMapper> imageSliceMapper = vtkSmartPointer<vtkImageSliceMapper>::New();
//        imageSliceMapper->SetInputData(image);
//        vtkSmartPointer<vtkImageSlice> imageSlice = vtkSmartPointer<vtkImageSlice>::New();
//        imageSlice->SetMapper(imageSliceMapper);
//        imageSlice->GetProperty()->SetOpacity(.5);
//        imageStack->AddImage(imageSlice);
//    }
//      //imageStack->SetActiveLayer(1);

//      // Setup renderers
//      vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
//      renderer->AddViewProp(imageStack);

//      ui->qvtkWidget->GetRenderWindow()->GetRenderers()->RemoveAllItems();
//      ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
//      ui->qvtkWidget->GetRenderWindow()->Render();

//}


//void RenderingWindow::on_actionopen_tif_Volume_triggered()
//{
//    QString directory = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
//    //QStringList fileNames = QFileDialog::getOpenFileNames( Q_NULLPTR, QObject::tr("Open Files"),"/path/to/file/",QObject::tr("Mesh Files (*.tiff *.tif)"));
//    if(directory == nullptr)
//    {
//        return;
//    }
//    ui->centralwidget->show();

//    vtkImageReader *reader = vtkImageReader::New();
//    reader->SetFilePrefix(directory.toStdString().c_str());
//    reader->SetFilePattern("/if6 1 5-4enero_Z%3d.tif");
//    reader->SetDataScalarTypeToUnsignedChar();

//    vtkStringArray *names = reader->GetFileNames();
//    if( names != nullptr)
//        vtkIdType s = names->GetSize();

//    vtkSmartPointer<vtkTIFFReader> header = vtkSmartPointer<vtkTIFFReader>::New();
//     QFile file(directory +"/if6 1 5-4enero_Z000.tif");
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//        return;
//    header->SetFileName(file.fileName().toStdString().c_str());
//    header->Update();


//    int height = header->GetDataExtent()[3];
//    int width = header->GetDataExtent()[1];
//    int depth = directory.count();

//    reader->SetDataExtent(0, width - 1, 0, height - 1, 0, depth - 1);
//    reader->SetDataScalarTypeToUnsignedChar();

//    reader->Update();

//    vtkObjectFactory::RegisterFactory(vtkRenderingOpenGL2ObjectFactory::New());
//    vtkObjectFactory::RegisterFactory(vtkRenderingVolumeOpenGL2ObjectFactory::New());

//    vtkFixedPointVolumeRayCastMapper *texMapper = vtkFixedPointVolumeRayCastMapper::New();
//    vtkVolume *vol = vtkVolume::New();
//    vtkColorTransferFunction *ctf = vtkColorTransferFunction::New();
//    vtkPiecewiseFunction *spwf = vtkPiecewiseFunction::New();
//    vtkPiecewiseFunction *gpwf = vtkPiecewiseFunction::New();

//    //Go through the visulizatin pipeline
//    texMapper->SetInputConnection(reader->GetOutputPort());

//    //Set the color curve for the volume
//      ctf->AddHSVPoint(0, .67, .07, 1);
//    ctf->AddHSVPoint(94, .67, .07, 1);
//    ctf->AddHSVPoint(139, 0, 0, 0);
//    ctf->AddHSVPoint(160, .28, .047, 1);
//    ctf->AddHSVPoint(254, .38, .013, 1);

//    //Set the opacity curve for the volume
//    spwf->AddPoint(84, 0);
//    spwf->AddPoint(151, .1);
//    spwf->AddPoint(255, 1);

//    //Set the gradient curve for the volume
//    gpwf->AddPoint(0, .2);
//    gpwf->AddPoint(10, .2);
//    gpwf->AddPoint(25, 1);

//    vol->GetProperty()->SetColor(ctf);
//    vol->GetProperty()->SetScalarOpacity(spwf);
//    vol->GetProperty()->SetGradientOpacity(gpwf);
//    vol->SetMapper(texMapper);

//    //Go through the Graphics Pipeline
//    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
//    renderer->AddVolume(vol);
//    //renderer->ResetCamera();

//    ui->qvtkWidget->GetRenderWindow()->GetRenderers()->RemoveAllItems();
//    ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
//    ui->qvtkWidget->GetRenderWindow()->Render();
//}

void RenderingWindow::on_actionopen_tif_Volume_triggered()
{
    QDir directory = QFileDialog::getExistingDirectory(this, tr("select directory"));
    if(!directory.exists())
    {
        return;
    }

    vtkImageReader *reader = vtkImageReader::New();
    //reader->SetFilePrefix(directory.absolutePath().toStdString().c_str());
    reader->SetDataScalarTypeToUnsignedChar();

    QStringList images = directory.entryList(QStringList() << "*.tif" << "*.tiff",QDir::Files);
    vtkStringArray *imagesName = vtkStringArray::New();
    for(QString image : images){
        imagesName->InsertNextValue(directory.absolutePath().toStdString() + "/" + image.toStdString());
    }
    reader->SetFileNames(imagesName);

    ui->centralwidget->show();

        int s = reader->GetFileNames()->GetNumberOfValues();

    vtkSmartPointer<vtkTIFFReader> header = vtkSmartPointer<vtkTIFFReader>::New();
    string fileName = reader->GetFileNames()->GetValue(0);
    header->SetFileName(fileName.c_str());
    header->Update();

    int height = header->GetDataExtent()[3];
    int width = header->GetDataExtent()[1];
    int depth = directory.count();

    reader->SetDataExtent(0, width - 1, 0, height - 1, 0, depth - 1);
    reader->SetDataScalarTypeToUnsignedChar();

    reader->Update();

    vtkObjectFactory::RegisterFactory(vtkRenderingOpenGL2ObjectFactory::New());
    vtkObjectFactory::RegisterFactory(vtkRenderingVolumeOpenGL2ObjectFactory::New());

    vtkFixedPointVolumeRayCastMapper *texMapper = vtkFixedPointVolumeRayCastMapper::New();
    vtkVolume *vol = vtkVolume::New();
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

    vol->GetProperty()->SetColor(ctf);
    vol->GetProperty()->SetScalarOpacity(spwf);
    vol->GetProperty()->SetGradientOpacity(gpwf);
    vol->SetMapper(texMapper);

    //Go through the Graphics Pipeline
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddVolume(vol);
        renderer->SetBackground(.2, .2, .2);
    //renderer->ResetCamera();

    ui->qvtkWidget->GetRenderWindow()->GetRenderers()->RemoveAllItems();
    ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
    ui->qvtkWidget->GetRenderWindow()->Render();
}

//void RenderingWindow::on_actionopen_tif_Volume_triggered()
//{
////    // Create the renderer, the render window, and the interactor. The renderer
////      // draws into the render window, the interactor enables mouse- and
////      // keyboard-based interaction with the scene.
////      vtkSmartPointer<vtkRenderer> ren =
////        vtkSmartPointer<vtkRenderer>::New();
////      vtkSmartPointer<vtkRenderWindow> renWin =
////        vtkSmartPointer<vtkRenderWindow>::New();
////      renWin->AddRenderer(ren);
////      vtkSmartPointer<vtkRenderWindowInteractor> iren =
////        vtkSmartPointer<vtkRenderWindowInteractor>::New();
////      iren->SetRenderWindow(renWin);

////      // The following reader is used to read a series of 2D slices (images)
////      // that compose the volume. The slice dimensions are set, and the
////      // pixel spacing. The data Endianness must also be specified. The reader
////      // uses the FilePrefix in combination with the slice number to construct
////      // filenames using the format FilePrefix.%d. (In this case the FilePrefix
////      // is the root name of the file: quarter.)
////      vtkSmartPointer<vtkTIFFReader> reader =
////        vtkSmartPointer<vtkTIFFReader>::New();
////          QStringList fileNames = QFileDialog::getOpenFileNames( Q_NULLPTR, QObject::tr("Open Files"),"/path/to/file/",QObject::tr("Mesh Files (*.tiff *.tif)"));
////          if(fileNames.isEmpty())
////          {
////              return;
////          }

////      reader->SetFileName(fileNames.at(0).toStdString().c_str());

////      string hola = reader->GetFilePattern();
////      // The volume will be displayed by ray-cast alpha compositing.
////      // A ray-cast mapper is needed to do the ray-casting.

////      vtkObjectFactory::RegisterFactory(vtkRenderingOpenGL2ObjectFactory::New());
////      vtkObjectFactory::RegisterFactory(vtkRenderingVolumeOpenGL2ObjectFactory::New());

////      vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> volumeMapper =
////        vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
////      volumeMapper->SetInputConnection(reader->GetOutputPort());

////      // The color transfer function maps voxel intensities to colors.
////      // It is modality-specific, and often anatomy-specific as well.
////      // The goal is to one color for flesh (between 500 and 1000)
////      // and another color for bone (1150 and over).
////      vtkSmartPointer<vtkColorTransferFunction>volumeColor =
////        vtkSmartPointer<vtkColorTransferFunction>::New();
////      volumeColor->AddRGBPoint(0,    0.0, 0.0, 0.0);
////      volumeColor->AddRGBPoint(500,  1.0, 0.5, 0.3);
////      volumeColor->AddRGBPoint(1000, 1.0, 0.5, 0.3);
////      volumeColor->AddRGBPoint(1150, 1.0, 1.0, 0.9);

////      // The opacity transfer function is used to control the opacity
////      // of different tissue types.
////      vtkSmartPointer<vtkPiecewiseFunction> volumeScalarOpacity =
////        vtkSmartPointer<vtkPiecewiseFunction>::New();
////      volumeScalarOpacity->AddPoint(0,    0.00);
////      volumeScalarOpacity->AddPoint(500,  0.15);
////      volumeScalarOpacity->AddPoint(1000, 0.15);
////      volumeScalarOpacity->AddPoint(1150, 0.85);

////      // The gradient opacity function is used to decrease the opacity
////      // in the "flat" regions of the volume while maintaining the opacity
////      // at the boundaries between tissue types.  The gradient is measured
////      // as the amount by which the intensity changes over unit distance.
////      // For most medical data, the unit distance is 1mm.
////      vtkSmartPointer<vtkPiecewiseFunction> volumeGradientOpacity =
////        vtkSmartPointer<vtkPiecewiseFunction>::New();
////      volumeGradientOpacity->AddPoint(0,   0.0);
////      volumeGradientOpacity->AddPoint(90,  0.5);
////      volumeGradientOpacity->AddPoint(100, 1.0);

////      // The VolumeProperty attaches the color and opacity functions to the
////      // volume, and sets other volume properties.  The interpolation should
////      // be set to linear to do a high-quality rendering.  The ShadeOn option
////      // turns on directional lighting, which will usually enhance the
////      // appearance of the volume and make it look more "3D".  However,
////      // the quality of the shading depends on how accurately the gradient
////      // of the volume can be calculated, and for noisy data the gradient
////      // estimation will be very poor.  The impact of the shading can be
////      // decreased by increasing the Ambient coefficient while decreasing
////      // the Diffuse and Specular coefficient.  To increase the impact
////      // of shading, decrease the Ambient and increase the Diffuse and Specular.
////      vtkSmartPointer<vtkVolumeProperty> volumeProperty =
////        vtkSmartPointer<vtkVolumeProperty>::New();
////      volumeProperty->SetColor(volumeColor);
////      volumeProperty->SetScalarOpacity(volumeScalarOpacity);
////      volumeProperty->SetGradientOpacity(volumeGradientOpacity);
////      volumeProperty->SetInterpolationTypeToLinear();
////      volumeProperty->ShadeOn();
////      volumeProperty->SetAmbient(0.4);
////      volumeProperty->SetDiffuse(0.6);
////      volumeProperty->SetSpecular(0.2);

////      // The vtkVolume is a vtkProp3D (like a vtkActor) and controls the position
////      // and orientation of the volume in world coordinates.
////      vtkSmartPointer<vtkVolume> volume =
////        vtkSmartPointer<vtkVolume>::New();
////      volume->SetMapper(volumeMapper);
////      volume->SetProperty(volumeProperty);

////      // Finally, add the volume to the renderer
////      ren->AddViewProp(volume);

////      // Set up an initial view of the volume.  The focal point will be the
////      // center of the volume, and the camera position will be 400mm to the
////      // patient's left (which is our right).
////      vtkCamera *camera = ren->GetActiveCamera();
////      double *c = volume->GetCenter();
////      camera->SetViewUp (0, 0, -1);
////      camera->SetPosition (c[0], c[1] - 400, c[2]);
////      camera->SetFocalPoint (c[0], c[1], c[2]);
////      camera->ComputeViewPlaneNormal();
////      camera->Azimuth(30.0);
////      camera->Elevation(30.0);

////      // Set a background color for the renderer
////      ren->SetBackground(.2, .3, .4);

////      renWin->SetSize(640, 480);
////      // Increase the size of the render window
////      renWin->SetSize(640, 480);

////      // Interact with the data.
////      iren->Initialize();
////      iren->Start();

////    QStringList fileNames = QFileDialog::getOpenFileNames( Q_NULLPTR, QObject::tr("Open Files"),"/path/to/file/",QObject::tr("Mesh Files (*.tiff *.tif)"));
////    if(fileNames.isEmpty())
////    {
////        return;
////    }

////    vtkSmartPointer<vtkTIFFReader> reader =
////        vtkSmartPointer<vtkTIFFReader>::New();
////      reader->SetFileName(fileNames.at(0).toStdString().c_str());
////      reader->Update();

////      // Visualize
////      vtkSmartPointer<vtkImageActor> actor =
////        vtkSmartPointer<vtkImageActor>::New();
////      actor->GetMapper()->SetInputConnection(reader->GetOutputPort());

////      vtkSmartPointer<vtkRenderer> renderer =
////        vtkSmartPointer<vtkRenderer>::New();
////      renderer->AddActor(actor);
////      renderer->ResetCamera();

////      vtkSmartPointer<vtkRenderWindow> renderWindow =
////        vtkSmartPointer<vtkRenderWindow>::New();
////      renderWindow->AddRenderer(renderer);

////      vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
////        vtkSmartPointer<vtkRenderWindowInteractor>::New();
////      vtkSmartPointer<vtkInteractorStyleImage> style =
////        vtkSmartPointer<vtkInteractorStyleImage>::New();

////      renderWindowInteractor->SetInteractorStyle(style);

////      renderWindowInteractor->SetRenderWindow(renderWindow);
////      renderWindowInteractor->Initialize();

////      renderWindowInteractor->Start();
//}
