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


TransformEditorObject::TransformEditorObject(QWidget *parent, Object *object, QVTKWidget *vtkWidget) : QWidget(parent)
{
    this->digits = 3;
    this->object = object;
    this->vtkWidget = vtkWidget;
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
        TifVolumeObject *obj = dynamic_cast<TifVolumeObject*>(object);
        if(obj != nullptr)
        {
            //double *pos = obj->getVolume()->GetPosition();
            double *center = obj->getVolume()->GetCenter();
            double *rot = obj->getVolume()->GetOrientation();
            double *sca = obj->getVolume()->GetScale();

//            positionXInput->setText(to_string(pos[0]).c_str());
//            positionYInput->setText(to_string(pos[1]).c_str());
//            positionZInput->setText(to_string(pos[2]).c_str());

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
//    double pos[3];
//    pos[0] = positionXInput->text().toDouble();
//    pos[1] = positionYInput->text().toDouble();
//    pos[2] = positionZInput->text().toDouble();

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
        position = obj->getActor()->GetPosition();
        //there's a bug in the y axis and the pos value has to be inverted
        //pos[1] = - pos[1];

        //obj->getActor()->SetPosition(pos);
//        obj->getActor()->SetOrientation(rot);
//        obj->getActor()->SetScale(sca);

        vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
        //move object to origin(0,0,0)
        transform->Translate(-center[0], -center[1], -center[2]);
        //scale object
        transform->Scale(sca[0], sca[1], sca[2]);
        //rotate object
        transform->RotateX(rot[0]);
        transform->RotateY(rot[1]);
        transform->RotateZ(rot[2]);
        //translate object to the desire point
        transform->Translate(tras[0], tras[1], tras[2]);

        if(obj->getActor()->GetUserMatrix())
        transform->Concatenate(obj->getActor()->GetUserMatrix());
        obj->getActor()->SetUserTransform(transform);

    }
    else
    {
        TifVolumeObject *obj = dynamic_cast<TifVolumeObject*>(object);
        if(obj != nullptr)
        {
            center = obj->getVolume()->GetCenter();
//            obj->getVolume()->SetPosition(pos);
//            obj->getVolume()->SetOrientation(rot);

            vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
            //move object to origin(0,0,0)
            transform->Translate(-center[0], -center[1], -center[2]);
            //scale object
            //transform->Scale(sca[0], sca[1], sca[2]);
            //rotate object
            transform->RotateX(rot[0]);
            transform->RotateY(rot[1]);
            transform->RotateZ(rot[2]);
            //translate object to the desire point
            transform->Translate(tras[0], tras[1], tras[2]);

            if(obj->getVolume()->GetUserMatrix())
                transform->Concatenate(obj->getVolume()->GetUserMatrix());
            obj->getVolume()->SetUserTransform(transform);
            obj->getVolume()->SetScale(sca);
        }
    }
    vtkWidget->GetRenderWindow()->Render();
}
