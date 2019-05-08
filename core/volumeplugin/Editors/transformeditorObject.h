#ifndef TRANSFORMEDITOR_H
#define TRANSFORMEDITOR_H

#include "QWidget"
#include "objectclasses/abstractclasses/object.h"
#include "vtkCamera.h"
#include "QLineEdit"
#include "QVTKWidget.h"
#include "Pairs/camerapropertiespair.h"
#include "QPushButton"
#include "Labels/clickablelabel.h"

class TransformEditorObject: public QWidget
{
    Q_OBJECT
public:
    TransformEditorObject(QWidget *parent, Object *object, QVTKWidget *vtkWidget, CameraPropertiesPair *cameraPair);

    int digits;
    QLineEdit *positionXInput;
    QLineEdit *positionYInput;
    QLineEdit *positionZInput;

    QLineEdit *rotationXInput;
    QLineEdit *rotationYInput;
    QLineEdit *rotationZInput;

    QLineEdit *scaleXInput;
    QLineEdit *scaleYInput;
    QLineEdit *scaleZInput;

    QPushButton *resetButton;

    ClickableLabel *label;
    QWidget *editor;

public slots:
    void updateObject(QString text);
    void resetTransform();
    void labelClicked();

private:
    Object *object;
    QVTKWidget *vtkWidget;
    CameraPropertiesPair *cameraPair;
};

#endif // TRANSFORMEDITOR_H
