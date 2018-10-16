#include "renderingwindow.h"
#include "ui_renderingwindow.h"
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


using namespace std;

RenderingWindow::RenderingWindow(QWidget *parent, Core *core) :
    QMainWindow(parent),
    ui(new Ui::RenderingWindow)
{
    ui->setupUi(this);
    QRect geometry = this->geometry();
    geometry.setHeight(20);
    this->setGeometry(geometry);
    ui->centralwidget->hide();
    ui->horizontalSlider->hide();
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
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    ui->qvtkWidget->SetRenderWindow(renderWindow);
}

void RenderingWindow::printTifObject(Object2D* obj)
{
    // Visualize
    vtkSmartPointer<vtkImageMapper> imageMapper = obj->getImageMapper();

    vtkSmartPointer<vtkImageResize> resize = vtkSmartPointer<vtkImageResize>::New();
    resize->SetInputData(obj->getOutputData());

    resize->SetOutputDimensions(ui->qvtkWidget->width(), ui->qvtkWidget->height(), 1);
    resize->Update();

    imageMapper->SetInputConnection(resize->GetOutputPort());

    vtkSmartPointer<vtkActor2D> image = vtkSmartPointer<vtkActor2D>::New();
    image->SetMapper(imageMapper);
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor2D(image);
    //renderer->AddActor(image);
    renderer->ResetCamera();
    renderer->SetBackground(.2, .2, .2);

    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    ui->qvtkWidget->SetRenderWindow(renderWindow);
}

void RenderingWindow::printObjects3D()
{

    for(Object3D *obj : *core->getObjects3D()){
        if(strcmp(obj->objectType(), "obj") == 0){
            printObjObject(obj);
        }
    }
}

void RenderingWindow::printObjects2D()
{

}

void RenderingWindow::on_actionopen_file_triggered()
{
    ui->centralwidget->show();
    QStringList fileNames = QFileDialog::getOpenFileNames( Q_NULLPTR, QObject::tr("Open File"),"/path/to/file/",QObject::tr("Mesh Files (*.obj *.tiff *.tif)"));
    string fileName = fileNames.at(0).toStdString();

    vector<string> splitName;
    boost::split(splitName, fileName, [](char c){return c == '.';});
    string ext = splitName.at(splitName.size() - 1);
    map<string, int> *fileExtMap = new map<string, int>();
        fileExtMap->insert(pair<string, int> ("obj", 1));
        fileExtMap->insert(pair<string, int> ("tif", 2));

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
                printTifObject(object);
               // core->addObject(object);
            }
            break;
        }
    }
}

void RenderingWindow::on_actionopen_stack_of_files_triggered()
{
    ui->centralwidget->show();
    ui->horizontalSlider->show();
    QStringList fileNames = QFileDialog::getOpenFileNames( Q_NULLPTR, QObject::tr("Open Files"),"/path/to/file/",QObject::tr("Mesh Files (*.tiff *.tif)"));

    for(QString name : fileNames){
        string fileName = name.toStdString();
        vector<string> splitName;
        boost::split(splitName, fileName, [](char c){return c == '.';});
        string ext = splitName.at(splitName.size() - 1);

        map<string, int> *fileExtMap = new map<string, int>();
            fileExtMap->insert(pair<string, int> ("tif", 1));

        switch(fileExtMap->find(ext)->second){
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

    ui->horizontalSlider->setMaximum(core->getObjects2D()->size() - 1);
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setValue(0);
    printTifObject(core->getObjects2D()->at(0));
}

void RenderingWindow::on_horizontalSlider_valueChanged(int value)
{
    printTifObject(core->getObjects2D()->at(value));
}
