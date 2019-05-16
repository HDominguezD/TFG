#include "graphicwindow.h"
#include "QKeyEvent"
#include "vtkAxesActor.h"
#include "vtkOrientationMarkerWidget.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkRendererCollection.h"
#include <iomanip>
#include <sstream>

GraphicWindow::GraphicWindow(QWidget *parent)
{
    this->setParent(parent);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(.2, .2, .2);

    this->GetRenderWindow()->AddRenderer(renderer);

    vtkRenderWindowInteractor *renderWindowInteractor = this->GetRenderWindow()->GetInteractor();

//    vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();

//    vtkSmartPointer<vtkOrientationMarkerWidget> widget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
//    widget->SetOutlineColor( 0.9300, 0.5700, 0.1300 );
//    widget->SetOrientationMarker( axes );
//    widget->SetInteractor(renderWindowInteractor);
//    widget->SetDefaultRenderer(renderer);
//    widget->SetViewport(0,0,0.2,0.2);
//    widget->SetEnabled( 1 );
//    widget->InteractiveOff();

    renderer->ResetCamera();
    this->GetRenderWindow()->Render();
    renderWindowInteractor->Start();
}

GraphicWindow::~GraphicWindow()
{
    this->~QVTKWidget();
}

void GraphicWindow::keyPressEvent(QKeyEvent *event)
{
    if(transformEditor)
    {
        double tras[3];
            tras[0] = transformEditor->positionXInput->text().toDouble();
            tras[1] = transformEditor->positionYInput->text().toDouble();
            tras[2] = transformEditor->positionZInput->text().toDouble();

        if(event->key() == Qt::Key_Left)
        {
            tras[0]--;
        }
        else if(event->key() == Qt::Key_Right)
        {
            tras[0]++;
        }
        else if(event->key() == Qt::Key_Down)
        {
            tras[1]--;
        }
        else if(event->key() == Qt::Key_Up)
        {
            tras[1]++;
        }
        else if(event->key() == Qt::Key_1)
        {
            tras[2]--;
        }
        else if(event->key() == Qt::Key_2)
        {
            tras[2]++;
        }
        stringstream stream;

        stream << fixed << setprecision(2) << tras[0];
        transformEditor->positionXInput->setText(stream.str().c_str());
        stream.str(std::string());
        stream << fixed << setprecision(2) << tras[1];
        transformEditor->positionYInput->setText(stream.str().c_str());
        stream.str(std::string());
        stream << fixed << setprecision(2) << tras[2];
        transformEditor->positionZInput->setText(stream.str().c_str());
        stream.str(std::string());

        transformEditor->updateObject("");
    }
}

void GraphicWindow::keyReleaseEvent(QKeyEvent *event)
{

}

void GraphicWindow::setTransformEditor(TransformEditorObject *value)
{
    transformEditor = value;
}
