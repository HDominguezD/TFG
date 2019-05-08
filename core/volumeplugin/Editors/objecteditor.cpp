#include "objecteditor.h"
#include "objectclasses/objobject.h"
#include "objectclasses/tifvolumeobject.h"
#include "QLabel"
#include "QGridLayout"
#include "QVBoxLayout"
#include "vtkRenderWindow.h"
#include "QFrame"

ObjectEditor::ObjectEditor(QWidget *parent, Object *object, QVTKWidget* widget)
{

    this->object = object;
    this->widget = widget;
    this->setParent(parent);

    ObjObject *obj = dynamic_cast<ObjObject*>(object);
    if(obj)
    {
        this->objectName = new QLineEdit(object->getName().c_str(), this);
        this->visible = new QCheckBox("Is Visible", this);
        this->visible->setChecked(obj->getActor()->GetVisibility());
        this->orientationAxes = new QCheckBox("Show orientation axes", this);
        this->orientationAxes->setChecked(obj->getAxes()->GetVisibility());
    }
    else
    {
        TifVolumeObject *vol = dynamic_cast<TifVolumeObject*>(object);
        if(vol)
        {
            this->objectName = new QLineEdit(object->getName().c_str(), this);
            this->visible = new QCheckBox("Is Visible", this);
            this->visible->setChecked(vol->getVolume()->GetVisibility());
            this->orientationAxes = new QCheckBox("Show orientation axes", this);
            this->orientationAxes->setChecked(vol->getAxes()->GetVisibility());
        }
    }

    label = new ClickableLabel(this);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setText("Object");
    label->setAlignment(Qt::AlignCenter);
    label->setFixedHeight(20);

    editor = new QWidget(this);
    QGridLayout *gridLayout = new QGridLayout(editor);
    QLabel *name = new QLabel(tr("Object Name"));
    gridLayout->addWidget(name, 0, 0);
    gridLayout->addWidget(objectName, 0, 1);
    gridLayout->addWidget(visible, 1, 0);
    gridLayout->addWidget(orientationAxes, 2, 0);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->addWidget(label);
    layout->addWidget(editor);

    this->setLayout(layout);

     connect(label, SIGNAL(clicked()), this, SLOT(labelClicked()));
     connect(objectName, SIGNAL(editingFinished()), this, SLOT(changeName()));
     connect(visible, SIGNAL(stateChanged(int)), this, SLOT(visibleChanged(int)));
     connect(orientationAxes, SIGNAL(stateChanged(int)), this, SLOT(orientationAxesChanged(int)));
}

Object *ObjectEditor::getObject() const
{
    return object;
}

void ObjectEditor::changeName()
{
    emit changeObjectName(this, objectName->text());
}

void ObjectEditor::visibleChanged(int status)
{
    ObjObject *obj = dynamic_cast<ObjObject*>(object);
    if(obj)
    {
        if(status)
        {
            obj->getActor()->VisibilityOn();
            if(orientationAxes->checkState())
            {
                obj->getAxes()->VisibilityOn();
            } else
            {
                obj->getAxes()->VisibilityOff();
            }
        }
        else
        {
            obj->getActor()->VisibilityOff();
            obj->getAxes()->VisibilityOff();

        }
    }
    else
    {
        TifVolumeObject *vol = dynamic_cast<TifVolumeObject*>(object);
        if(vol)
        {
            if(status)
            {
                vol->getVolume()->VisibilityOn();
                if(orientationAxes->checkState())
                {
                    vol->getAxes()->VisibilityOn();
                } else
                {
                    vol->getAxes()->VisibilityOff();
                }
            }
            else
            {
                vol->getVolume()->VisibilityOff();
                vol->getAxes()->VisibilityOff();
            }
        }
    }
    widget->GetRenderWindow()->Render();
}

void ObjectEditor::orientationAxesChanged(int status)
{
    ObjObject *obj = dynamic_cast<ObjObject*>(object);
    if(obj)
    {
        if(status && visible->checkState())
        {
            obj->getAxes()->VisibilityOn();
        } else
        {
            obj->getAxes()->VisibilityOff();
        }
    }
    else
    {
        TifVolumeObject *vol = dynamic_cast<TifVolumeObject*>(object);
        if(vol)
        {
            if(status && visible->checkState())
            {
                vol->getAxes()->VisibilityOn();
            } else
            {
                vol->getAxes()->VisibilityOff();
            }
        }
    }
    widget->GetRenderWindow()->Render();
}

void ObjectEditor::labelClicked()
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
