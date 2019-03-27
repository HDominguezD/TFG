#ifndef TRANSFORMEDITORCAMERA_H
#define TRANSFORMEDITORCAMERA_H

#include "vtkCamera.h"
#include "qwidget.h"
#include "QLineEdit"
#include "QVTKWidget.h"

class TransformEditorCamera : public QWidget
{
    Q_OBJECT
public:
    TransformEditorCamera(QWidget *parent, vtkCamera *camera, QVTKWidget *vtkWidget);
    void updateFocalPoint(double *fP);

    int digits;

private slots:
    void updateCamera();

private:
    vtkCamera *camera;
    QVTKWidget *vtkWidget;

    QLineEdit *positionXInput;
    QLineEdit *positionYInput;
    QLineEdit *positionZInput;

    QLineEdit *fPointXInput;
    QLineEdit *fPointYInput;
    QLineEdit *fPointZInput;
};

#endif // TRANSFORMEDITORCAMERA_H
