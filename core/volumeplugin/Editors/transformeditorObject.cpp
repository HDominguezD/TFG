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

    label = new ClickableLabel(this);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setText("Transform");
    label->setAlignment(Qt::AlignCenter);
    label->setFixedHeight(20);

    editor = new QWidget(this);
    QGridLayout *gridLayout = new QGridLayout(editor);

    QRegExpValidator *val = new QRegExpValidator(QRegExp("[--+]?[0-9]+.[0-9][0-9]"));

    QLabel *position = new QLabel(tr("Position"));
    QLabel *positionX = new QLabel(tr("X"));

    resetButton = new QPushButton(this);
    resetButton->setText("Reset");


    positionXInput = new QLineEdit(this);
    positionXInput->setObjectName("PositionXInput");
    positionXInput->setValidator(val);

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

    gridLayout->addWidget(position, 0, 0);
    gridLayout->addWidget(positionX, 0, 1);
    gridLayout->addWidget(positionXInput, 0, 2);
    gridLayout->addWidget(positionY, 0, 3);
    gridLayout->addWidget(positionYInput, 0, 4);
    gridLayout->addWidget(positionZ, 0, 5);
    gridLayout->addWidget(positionZInput, 0, 6);

    gridLayout->addWidget(rotation, 1, 0);
    gridLayout->addWidget(rotationX, 1, 1);
    gridLayout->addWidget(rotationXInput, 1, 2);
    gridLayout->addWidget(rotationY, 1, 3);
    gridLayout->addWidget(rotationYInput, 1, 4);
    gridLayout->addWidget(rotationZ, 1, 5);
    gridLayout->addWidget(rotationZInput, 1, 6);

    gridLayout->addWidget(scale, 2, 0);
    gridLayout->addWidget(scaleX, 2, 1);
    gridLayout->addWidget(scaleXInput, 2, 2);
    gridLayout->addWidget(scaleY, 2, 3);
    gridLayout->addWidget(scaleYInput, 2, 4);
    gridLayout->addWidget(scaleZ, 2, 5);
    gridLayout->addWidget(scaleZInput, 2, 6);
    gridLayout->addWidget(resetButton, 3, 6);

    double *center;
    double *rot;
    double *sca;

    ObjObject *obj = dynamic_cast<ObjObject*>(object);
    if(obj != nullptr)
    {
        //double *pos = obj->getActor()->GetPosition();
        center = obj->getActor()->GetCenter();
        rot = obj->getActor()->GetOrientation();
        sca = obj->getActor()->GetScale();
    }
    else
    {
        TifVolumeObject *vol = dynamic_cast<TifVolumeObject*>(object);
        if(vol != nullptr)
        {
            center = vol->getVolume()->GetCenter();
            rot = vol->getVolume()->GetOrientation();
            sca = vol->getVolume()->GetScale();
        }
    }

    if(center && rot && sca)
    {
        stringstream stream;

        stream << fixed << setprecision(2) << center[0];
        positionXInput->setText(stream.str().c_str());
        stream.str(std::string());
        stream << fixed << setprecision(2) << center[1];
        positionYInput->setText(stream.str().c_str());
        stream.str(std::string());
        stream << fixed << setprecision(2) << center[2];
        positionZInput->setText(stream.str().c_str());
        stream.str(std::string());


        stream << fixed << setprecision(2) << rot[0];
        rotationXInput->setText(stream.str().c_str());
        stream.str(std::string());
        stream << fixed << setprecision(2) << rot[1];
        rotationYInput->setText(stream.str().c_str());
        stream.str(std::string());
        stream << fixed << setprecision(2) << rot[2];
        rotationZInput->setText(stream.str().c_str());
        stream.str(std::string());

        stream << fixed << setprecision(2) << sca[0];
        scaleXInput->setText(stream.str().c_str());
        stream.str(std::string());
        stream << fixed << setprecision(2) << sca[1];
        scaleYInput->setText(stream.str().c_str());
        stream.str(std::string());
        stream << fixed << setprecision(2) << sca[2];
        scaleZInput->setText(stream.str().c_str());
        stream.str(std::string());

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignTop);
        layout->addWidget(label);
        layout->addWidget(editor);

        this->setLayout(layout);
    }

    connect(label, SIGNAL(clicked()), this, SLOT(labelClicked()));
    connect(resetButton, SIGNAL(released()), this, SLOT(resetTransform()));

    connect(positionXInput, SIGNAL(textEdited(QString)), this, SLOT(updateObject(QString)));
    connect(positionYInput, SIGNAL(textEdited(QString)), this, SLOT(updateObject(QString)));
    connect(positionZInput, SIGNAL(textEdited(QString)), this, SLOT(updateObject(QString)));

    connect(rotationXInput, SIGNAL(textEdited(QString)), this, SLOT(updateObject(QString)));
    connect(rotationYInput, SIGNAL(textEdited(QString)), this, SLOT(updateObject(QString)));
    connect(rotationZInput, SIGNAL(textEdited(QString)), this, SLOT(updateObject(QString)));

    connect(scaleXInput, SIGNAL(textEdited(QString)), this, SLOT(updateObject(QString)));
    connect(scaleYInput, SIGNAL(textEdited(QString)), this, SLOT(updateObject(QString)));
    connect(scaleZInput, SIGNAL(textEdited(QString)), this, SLOT(updateObject(QString)));

}

void TransformEditorObject::updateObject(QString text)
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

//    TransformEditorCamera *editorCamera = cameraPair->getPropertiesDock()->findChild<TransformEditorCamera *>("Transform Editor Camera");
//    editorCamera->updateFocalPoint(tras);
//    cameraPair->getCamera()->SetFocalPoint(tras[0], tras[1], tras[2]);
    vtkWidget->GetRenderWindow()->Render();
}

void TransformEditorObject::resetTransform()
{
    positionXInput->setText("0");
    positionYInput->setText("0");
    positionZInput->setText("0");

    rotationXInput->setText("0");
    rotationYInput->setText("0");
    rotationZInput->setText("0");

    scaleXInput->setText("1");
    scaleYInput->setText("1");
    scaleZInput->setText("1");

    updateObject("");
}

void TransformEditorObject::labelClicked()
{
    if(editor->isVisible())
    {
        editor->setVisible(false);
        label->setStyleSheet("QLabel { background-color : #C4C4C0  ; }");
    }
    else
    {
        editor->setVisible(true);
        label->setStyleSheet("");

    }
}
