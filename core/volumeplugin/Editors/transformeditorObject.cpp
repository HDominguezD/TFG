#include "transformeditorObject.h"
#include "QLabel"
#include "QGridLayout"
#include "QLineEdit"
#include "QDoubleValidator"
#include "QFont"
#include "objectclasses/objobject.h"
#include "objectclasses/tifvolumeobject.h"
#include "vtkTransform.h"
#include "vtkRenderWindow.h"
#include "Editors/transformeditorcamera.h"


TransformEditorObject::TransformEditorObject(QWidget *parent, Object *object, QVTKWidget *vtkWidget, CameraPropertiesPair *cameraPair) : QWidget(parent)
{
    this->digits = 3;
    this->object = object;
    this->vtkWidget = vtkWidget;
    this->cameraPair = cameraPair;
    this->setParent(parent);
    QFont *font = new QFont(this->font());
    font->setPointSize(9);
    this->setFont(*font);
    QGridLayout *layout = new QGridLayout(this);

    QDoubleValidator *val = new QDoubleValidator(0);
    val->setDecimals(digits);

    QLabel *position = new QLabel(tr("Position"));
    QLabel *positionX = new QLabel(tr("X"));
    positionXInput = new QLineEdit(this);
    positionXInput->setObjectName("PositionXInput");
    positionXInput->setValidator( val);

    QLabel *positionY = new QLabel(tr("Y"));
    positionYInput = new QLineEdit(this);
    positionYInput->setObjectName("PositionYInput");
    positionYInput->setValidator( val);

    QLabel *positionZ = new QLabel(tr("Z"));
    positionZInput = new QLineEdit(this);
    positionZInput->setObjectName("PositionZInput");
    positionZInput->setValidator( val);

    QLabel *rotation = new QLabel(tr("Rotation"));
    QLabel *rotationX = new QLabel(tr("X"));
    rotationXInput = new QLineEdit(this);
    rotationXInput->setObjectName("RotationXInput");
    rotationXInput->setValidator( val);

    QLabel *rotationY = new QLabel(tr("Y"));
    rotationYInput = new QLineEdit(this);
    rotationYInput->setObjectName("RotationYInput");
    rotationYInput->setValidator( val);

    QLabel *rotationZ = new QLabel(tr("Z"));
    rotationZInput = new QLineEdit(this);
    rotationZInput->setObjectName("RotationZInput");
    rotationZInput->setValidator( val);

    QLabel *scale = new QLabel(tr("Scale"));
    QLabel *scaleX = new QLabel(tr("X"));
    scaleXInput = new QLineEdit(this);
    scaleXInput->setObjectName("ScaleXInput");
    scaleXInput->setValidator(val);

    QLabel *scaleY = new QLabel(tr("Y"));
    scaleYInput = new QLineEdit(this);
    scaleYInput->setObjectName("ScaleYInput");
    scaleYInput->setValidator( val);

    QLabel *scaleZ = new QLabel(tr("Z"));
    scaleZInput = new QLineEdit(this);
    scaleZInput->setObjectName("ScaleZInput");
    scaleZInput->setValidator( val);

    layout->addWidget(position, 0, 0);
    layout->addWidget(positionX, 0, 1);
    layout->addWidget(positionXInput, 0, 2);
    layout->addWidget(positionY, 0, 3);
    layout->addWidget(positionYInput, 0, 4);
    layout->addWidget(positionZ, 0, 5);
    layout->addWidget(positionZInput, 0, 6);

    layout->addWidget(rotation, 1, 0);
    layout->addWidget(rotationX, 1, 1);
    layout->addWidget(rotationXInput, 1, 2);
    layout->addWidget(rotationY, 1, 3);
    layout->addWidget(rotationYInput, 1, 4);
    layout->addWidget(rotationZ, 1, 5);
    layout->addWidget(rotationZInput, 1, 6);

    layout->addWidget(scale, 2, 0);
    layout->addWidget(scaleX, 2, 1);
    layout->addWidget(scaleXInput, 2, 2);
    layout->addWidget(scaleY, 2, 3);
    layout->addWidget(scaleYInput, 2, 4);
    layout->addWidget(scaleZ, 2, 5);
    layout->addWidget(scaleZInput, 2, 6);

    ObjObject *obj = dynamic_cast<ObjObject*>(object);
    if(obj != nullptr)
    {
        //double *pos = obj->getActor()->GetPosition();
        double *center = obj->getActor()->GetCenter();
        double *rot = obj->getActor()->GetOrientation();
        double *sca = obj->getActor()->GetScale();

        positionXInput->setText(to_string(center[0]).c_str());
        positionYInput->setText(to_string(center[1]).c_str());
        positionZInput->setText(to_string(center[2]).c_str());

        rotationXInput->setText(to_string(rot[0]).c_str());
        rotationYInput->setText(to_string(rot[1]).c_str());
        rotationZInput->setText(to_string(rot[2]).c_str());

        scaleXInput->setText(to_string(sca[0]).c_str());
        scaleYInput->setText(to_string(sca[1]).c_str());
        scaleZInput->setText(to_string(sca[2]).c_str());

        this->setLayout(layout);
    }
    else
    {
        TifVolumeObject *vol = dynamic_cast<TifVolumeObject*>(object);
        if(vol != nullptr)
        {
            double *center = vol->getVolume()->GetCenter();
            double *rot = vol->getVolume()->GetOrientation();
            double *sca = vol->getVolume()->GetScale();

            positionXInput->setText(to_string(center[0]).c_str());
            positionYInput->setText(to_string(center[1]).c_str());
            positionZInput->setText(to_string(center[2]).c_str());

            rotationXInput->setText(to_string(rot[0]).c_str());
            rotationYInput->setText(to_string(rot[1]).c_str());
            rotationZInput->setText(to_string(rot[2]).c_str());

            scaleXInput->setText(to_string(sca[0]).c_str());
            scaleYInput->setText(to_string(sca[1]).c_str());
            scaleZInput->setText(to_string(sca[2]).c_str());
            this->setLayout(layout);
        }
    }

    connect(positionXInput, SIGNAL(editingFinished()), this, SLOT(updateObject()));
    connect(positionYInput, SIGNAL(editingFinished()), this, SLOT(updateObject()));
    connect(positionZInput, SIGNAL(editingFinished()), this, SLOT(updateObject()));

    connect(rotationXInput, SIGNAL(editingFinished()), this, SLOT(updateObject()));
    connect(rotationYInput, SIGNAL(editingFinished()), this, SLOT(updateObject()));
    connect(rotationZInput, SIGNAL(editingFinished()), this, SLOT(updateObject()));

    connect(scaleXInput, SIGNAL(editingFinished()), this, SLOT(updateObject()));
    connect(scaleYInput, SIGNAL(editingFinished()), this, SLOT(updateObject()));
    connect(scaleZInput, SIGNAL(editingFinished()), this, SLOT(updateObject()));

}

void TransformEditorObject::updateObject()
{
    double *center;
    double *position;

    double tras[3];
        tras[0] = positionXInput->text().toDouble();
        tras[1] = positionYInput->text().toDouble();
        tras[2] = positionZInput->text().toDouble();
    double rot[3];
        rot[0] = rotationXInput->text().toDouble();
        rot[1] = rotationYInput->text().toDouble();
        rot[2] = rotationZInput->text().toDouble();
    double sca[3];
        sca[0] = scaleXInput->text().toDouble();
        sca[1] = scaleYInput->text().toDouble();
        sca[2] = scaleZInput->text().toDouble();

    ObjObject *obj = dynamic_cast<ObjObject*>(object);
    if(obj != nullptr)
    {
        center = obj->getActor()->GetCenter();

        vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
        transform->PostMultiply();

        vtkSmartPointer<vtkTransform> axesTransform = vtkSmartPointer<vtkTransform>::New();
        axesTransform->PostMultiply();

        //reset traslation
        transform->Translate(-center[0], -center[1], -center[2]);

        //update translation
        transform->Translate(tras[0], tras[1], tras[2]);
        if(obj->getActor()->GetUserMatrix())
            transform->Concatenate(obj->getActor()->GetUserMatrix());
        obj->getActor()->SetUserTransform(transform);

        axesTransform->Translate(tras[0], tras[1], tras[2]);
        obj->getAxes()->SetUserTransform(axesTransform);

        //reset scale
        double *scale = obj->getActor()->GetScale();
        obj->getActor()->SetScale(1 / scale[0], 1 / scale[1], 1 / scale[2]);

        //update scale
        obj->getActor()->SetScale(sca[0], sca[1], sca[2]);

        double bounds[3];
        bounds[0] = obj->getActor()->GetBounds()[0];
        bounds[1] = obj->getActor()->GetBounds()[1];
        bounds[2] = obj->getActor()->GetBounds()[2];

        double minorBound = bounds[0];
        for(int i = 1; i < 3; i++)
        {
          if (minorBound > bounds[i])
              minorBound = bounds[i];
        }
        double sca = std::abs(minorBound)/ 8;
        obj->getAxes()->SetTotalLength(sca, sca, sca);

        //reset rotation
        double *orientation = obj->getActor()->GetOrientation();
        obj->getActor()->RotateX(-orientation[0]);
        obj->getActor()->RotateY(-orientation[1]);
        obj->getActor()->RotateZ(-orientation[2]);

        obj->getAxes()->RotateX(-orientation[0]);
        obj->getAxes()->RotateY(-orientation[1]);
        obj->getAxes()->RotateZ(-orientation[2]);

        //update rotation
        obj->getActor()->RotateX(rot[0]);
        obj->getActor()->RotateY(rot[1]);
        obj->getActor()->RotateZ(rot[2]);

        obj->getAxes()->RotateX(rot[0]);
        obj->getAxes()->RotateY(rot[1]);
        obj->getAxes()->RotateZ(rot[2]);
    }
    else
    {
        TifVolumeObject *vol = dynamic_cast<TifVolumeObject*>(object);
        if(vol != nullptr)
        {
            center = vol->getVolume()->GetCenter();

            vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
            transform->PostMultiply();

            vtkSmartPointer<vtkTransform> axesTransform = vtkSmartPointer<vtkTransform>::New();
            axesTransform->PostMultiply();

            //reset traslation
            transform->Translate(-center[0], -center[1], -center[2]);

            //update translation
            transform->Translate(tras[0], tras[1], tras[2]);
            if(vol->getVolume()->GetUserMatrix())
                transform->Concatenate(vol->getVolume()->GetUserMatrix());
            vol->getVolume()->SetUserTransform(transform);

            axesTransform->Translate(tras[0], tras[1], tras[2]);
            vol->getAxes()->SetUserTransform(axesTransform);

            //reset scale
            double *scale = vol->getVolume()->GetScale();
            vol->getVolume()->SetScale(1 / scale[0], 1 / scale[1], 1 / scale[2]);

            //update scale
            vol->getVolume()->SetScale(sca[0], sca[1], sca[2]);

            double bounds[3];
            bounds[0] = vol->getVolume()->GetBounds()[0];
            bounds[1] = vol->getVolume()->GetBounds()[1];
            bounds[2] = vol->getVolume()->GetBounds()[2];

            double minorBound = bounds[0];
            for(int i = 1; i < 3; i++)
            {
              if (minorBound > bounds[i])
                  minorBound = bounds[i];
            }
            double sca = std::abs(minorBound)/ 8;
            vol->getAxes()->SetTotalLength(sca, sca, sca);

            //reset rotation
            double *orientation = vol->getVolume()->GetOrientation();
            vol->getVolume()->RotateX(-orientation[0]);
            vol->getVolume()->RotateY(-orientation[1]);
            vol->getVolume()->RotateZ(-orientation[2]);

            vol->getAxes()->RotateX(-orientation[0]);
            vol->getAxes()->RotateY(-orientation[1]);
            vol->getAxes()->RotateZ(-orientation[2]);

            //update rotation
            vol->getVolume()->RotateX(rot[0]);
            vol->getVolume()->RotateY(rot[1]);
            vol->getVolume()->RotateZ(rot[2]);

            vol->getAxes()->RotateX(rot[0]);
            vol->getAxes()->RotateY(rot[1]);
            vol->getAxes()->RotateZ(rot[2]);
        }
    }

    TransformEditorCamera *editorCamera = cameraPair->getPropertiesDock()->findChild<TransformEditorCamera *>("Transform Editor Camera");
    editorCamera->updateFocalPoint(tras);
    cameraPair->getCamera()->SetFocalPoint(tras[0], tras[1], tras[2]);
    vtkWidget->GetRenderWindow()->Render();
}
