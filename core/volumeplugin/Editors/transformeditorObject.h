#ifndef TRANSFORMEDITOR_H
#define TRANSFORMEDITOR_H

#include "QWidget"
#include "objectclasses/abstractclasses/object.h"
#include "vtkCamera.h"
#include "QLineEdit"
#include "QVTKWidget.h"
#include "Pairs/camerapropertiespair.h"

class TransformEditorObject: public QWidget
{
    Q_OBJECT
public:
    TransformEditorObject(QWidget *parent, Object *object, QVTKWidget *vtkWidget, CameraPropertiesPair *cameraPair);

    int digits;

private slots:
    void updateObject();

private:
    Object *object;
    QVTKWidget *vtkWidget;
    CameraPropertiesPair *cameraPair;
    QLineEdit *positionXInput;
    QLineEdit *positionYInput;
    QLineEdit *positionZInput;

    QLineEdit *rotationXInput;
    QLineEdit *rotationYInput;
    QLineEdit *rotationZInput;

    QLineEdit *scaleXInput;
    QLineEdit *scaleYInput;
    QLineEdit *scaleZInput;
};

#endif // TRANSFORMEDITOR_H
