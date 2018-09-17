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
    renderer->SetBackground(.255,.255,.255); // Background color salmon

    for(int i = 0; i < obj->getFaces()->size(); i++)
    {
        // Create a mapper and actor
        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputData(obj->getFaces()->at(i));

        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);
        renderer->AddActor(actor);
    }

    // VTK/Qt wedded
    ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);

    // Set up action signals and slots
    //connect(this->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));

}
