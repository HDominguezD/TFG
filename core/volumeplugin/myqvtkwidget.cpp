#include "myqvtkwidget.h"
#include "QVTKWidget.h"
#include "QEvent"
#include "QKeyEvent"
#include "vtkRendererCollection.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "math.h"
#include "vtkCamera.h"

MyQVTKWidget::MyQVTKWidget()
{
}

void MyQVTKWidget::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
        case Qt::Key_Up:
        {
            vtkRenderer *renderer = this->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
            vtkCamera *camera = renderer->GetActiveCamera();
            double *focalPoint = camera->GetFocalPoint();
            double *actualPosition = camera->GetPosition();

            double *newPos = new double();
            newPos[0] = (focalPoint[0] + actualPosition[0])/1.25;
            newPos[1] = (focalPoint[1] + actualPosition[1])/1.25;
            newPos[2] = (focalPoint[2] + actualPosition[2])/1.25;

            camera->SetPosition(newPos);


            this->GetRenderWindow()->Render();

            break;
        }
        case Qt::Key_Down:
        {
            vtkRenderer *renderer = this->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
            vtkCamera *camera = renderer->GetActiveCamera();
            double *focalPoint = camera->GetFocalPoint();
            double *actualPosition = camera->GetPosition();

            double *newPos = new double();
            newPos[0] = (focalPoint[0] + actualPosition[0])*1.25;
            newPos[1] = (focalPoint[1] + actualPosition[1])*1.25;
            newPos[2] = (focalPoint[2] + actualPosition[2])*1.25;

            camera->SetPosition(newPos);

            this->GetRenderWindow()->Render();

            break;
        }
        case Qt::Key_Left:
        {
            vtkRenderer *renderer = this->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
            vtkCamera *camera = renderer->GetActiveCamera();
            double *focalPoint = camera->GetFocalPoint();
            double *actualPosition = camera->GetPosition();

            double *ratioVector = new double();
            ratioVector[0] = (focalPoint[0] + actualPosition[0]);
            ratioVector[1] = (focalPoint[1] + actualPosition[1]);
            ratioVector[2] = (focalPoint[2] + actualPosition[2]);

            //rotate around the Y axis
            //circunference equation pow((x ─ a),2) + pow((y ─ b),2) = pow(r,2);
            //circunference of the camera move around the focal point

            //r = sqrt(pow((x - x1),2) + pow((y - y1),2))

            //rect1 equation y = m*x + n;
            //rect to join focal point with the new camera position

            //rect2 equation (x -x1) / (x2-x1) = (y - y1) / (y2 -y1);
            //rect to join focal point with the actual camera position

            //n = x when in rect2 y = 0;
            // x = ((-y1) * (x2 - x1)) / (y2 -y1) + x1

            //m = tan(angle);
            //slope of the rect 1

            //angle = 15º;
            //cause i want to move around the focal point each 15º

            //the new camera position will be the intersection between
            //circunference equation and rect1 equation

            int angle = 15;
            double m = tan(angle);
            int n = ((-focalPoint[1] * (actualPosition[0] - focalPoint[0])) / (actualPosition[1] - focalPoint[1])) + focalPoint[0];

            double ratioModule = sqrt(pow(ratioVector[0], 2) + pow(ratioVector[1], 2));

            double *newPos = new double();
            newPos[0] = (focalPoint[0] + actualPosition[0])*1.25;
            newPos[1] = (focalPoint[1] + actualPosition[1])*1.25;
            newPos[2] = (focalPoint[2] + actualPosition[2])*1.25;
            camera->SetPosition(newPos);

            this->GetRenderWindow()->Render();
             break;
        }
        case Qt::Key_Right:
        {

             break;
        }
        default:
        {
            QVTKWidget::keyPressEvent(event);
        }
    }
}
