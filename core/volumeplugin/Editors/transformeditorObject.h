#ifndef TRANSFORMEDITOR_H
#define TRANSFORMEDITOR_H

#include "QWidget"
#include "objectclasses/abstractclasses/object.h"
#include "vtkCamera.h"
#include "QLineEdit"
#include "QVTKWidget.h"

class TransformEditorObject: public QWidget
{
    Q_OBJECT
public:
    TransformEditorObject(QWidget *parent, Object *object, QVTKWidget *vtkWidget);

    QLineEdit *positionXInput;
    QLineEdit *positionYInput;
    QLineEdit *positionZInput;

    QLineEdit *rotationXInput;
    QLineEdit *rotationYInput;
    QLineEdit *rotationZInput;

    QLineEdit *scaleXInput;
    QLineEdit *scaleYInput;
    QLineEdit *scaleZInput;

    int digits;

private slots:
    void updateObject();

private:
    Object *object;
    QVTKWidget *vtkWidget;
};

#endif // TRANSFORMEDITOR_H
