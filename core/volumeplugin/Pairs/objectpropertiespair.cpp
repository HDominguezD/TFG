#include "objectpropertiespair.h"

ObjectPropertiesPair::ObjectPropertiesPair(Object *object, QDockWidget *propertiesDock)
{
    this->object = object;
    this->propertiesDock = propertiesDock;
}

Object *ObjectPropertiesPair::getObject() const
{
    return object;
}

void ObjectPropertiesPair::setObject(Object *value)
{
    object = value;
}

QDockWidget *ObjectPropertiesPair::getPropertiesDock() const
{
    return propertiesDock;
}

void ObjectPropertiesPair::setPropertiesDock(QDockWidget *value)
{
    propertiesDock = value;
}
