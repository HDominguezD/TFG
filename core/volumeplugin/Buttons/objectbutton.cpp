#include "objectbutton.h"

ObjectButton::ObjectButton(ObjectPropertiesPair *objectPropertiesPair, QWidget *parent)
{
    this->objectPropertiesPair = objectPropertiesPair;
    this->setParent(parent);
    connect(this, SIGNAL(clicked(bool)), this, SLOT(buttonClicked(bool)));
}

void ObjectButton::buttonClicked(bool clicked)
{
    emit objectButtonClicked(objectPropertiesPair);
}
