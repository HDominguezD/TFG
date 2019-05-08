#ifndef TRANSFORMEDITORCAMERA_H
#define TRANSFORMEDITORCAMERA_H

#include "vtkCamera.h"
#include "qwidget.h"
#include "QLineEdit"
#include "QVTKWidget.h"
#include "Labels/clickablelabel.h"

class TransformEditorCamera : public QWidget
{
    Q_OBJECT
public:
    TransformEditorCamera(QWidget *parent, vtkCamera *camera, QVTKWidget *vtkWidget);
    void updateFocalPoint(double *fP);

    int digits;
    ClickableLabel *label;
    QWidget *editor;

private slots:
    void updateCamera(QString text);
    void labelClicked();

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
