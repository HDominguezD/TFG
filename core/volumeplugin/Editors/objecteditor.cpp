#include "objecteditor.h"
#include "objectclasses/objobject.h"
#include "objectclasses/tifvolumeobject.h"
#include "QLabel"
#include "QGridLayout"
#include "vtkRenderWindow.h"

ObjectEditor::ObjectEditor(QWidget *parent, Object *object, QVTKWidget* widget)
{

    this->object = object;
    this->widget = widget;
    this->setParent(parent);

    ObjObject *obj = dynamic_cast<ObjObject*>(object);
    if(obj)
    {
        this->objectName = new QLineEdit("Obj object", this);
        this->visible = new QCheckBox("Is Visible", this);
        this->visible->setChecked(obj->getActor()->GetVisibility());
    }
    else
    {
        TifVolumeObject *vol = dynamic_cast<TifVolumeObject*>(object);
        if(vol)
        {
            this->objectName = new QLineEdit("Volume object", this);
            this->visible = new QCheckBox("Is Visible", this);
            this->visible->setChecked(vol->getVolume()->GetVisibility());
        }
    }

    QGridLayout *layout = new QGridLayout(this);
    QLabel *name = new QLabel(tr("Object Name"));
    layout->addWidget(name, 0, 0);
    layout->addWidget(objectName, 0, 1);
    layout->addWidget(visible, 1, 0);

    this->setLayout(layout);

     connect(objectName, SIGNAL(editingFinished()), this, SLOT(changeName()));
     connect(visible, SIGNAL(stateChanged(int)), this, SLOT(visibleChanged(int)));
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
        }
        else
        {
            obj->getActor()->VisibilityOff();
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
            }
            else
            {
                vol->getVolume()->VisibilityOff();
            }
        }
    }
    widget->GetRenderWindow()->Render();
}
