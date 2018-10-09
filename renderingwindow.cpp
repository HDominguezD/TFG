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



RenderingWindow::RenderingWindow(QWidget *parent, Core *core) :
    QWidget(parent),
    ui(new Ui::RenderingWindow)
{
    ui->setupUi(this);
    this->core = core;
}

RenderingWindow::~RenderingWindow()
{
    delete ui;
}

void RenderingWindow::printObjObject(Object3D* obj)
{
//    // Visualize
//    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
//    renderer->SetBackground(0, 0, 0); // Background color salmon

//    // Create a mapper and actor
//    vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
//    mapper->SetInputData(obj->getObject());

//    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
//    actor->SetMapper(mapper);
//    renderer->AddActor(actor);

//    // VTK/Qt wedded
//    ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

    // Visualize
    vtkSmartPointer<vtkPolyDataMapper> mapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(obj->getObject());

    vtkSmartPointer<vtkActor> actor =
      vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderer> renderer =
      vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(.3, .6, .3); // Background color green

    vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderWindowInteractor->Start();

     ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

}

void RenderingWindow::printObjects()
{
    for(Object3D *obj : *core->getObjects()){
        if(strcmp(obj->objectType(), "obj") == 0){
            printObjObject(obj);
        }
    }
}
