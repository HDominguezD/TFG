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



RenderingWindow::RenderingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderingWindow)
{
    ui->setupUi(this);
}

RenderingWindow::~RenderingWindow()
{
    delete ui;
}

void RenderingWindow::printObjObject(ObjObject* obj)
{
    // Visualize
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(0, 0, 0); // Background color salmon

    // Create a mapper and actor
    vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
    mapper->SetInputData(obj->getObject());

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    renderer->AddActor(actor);

    // VTK/Qt wedded
    ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

    // Set up action signals and slots
    //connect(this->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));

}
