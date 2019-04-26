#include "objecttreewidgetitem.h"

ObjectTreeWidgetItem::ObjectTreeWidgetItem(ObjectPropertiesPair *objectPropertiesPair)
{
    this->objectPropertiesPair = objectPropertiesPair;
    this->setText(0, objectPropertiesPair->getObject()->getName().c_str());
}

ObjectPropertiesPair *ObjectTreeWidgetItem::getObjectPropertiesPair() const
{
    return objectPropertiesPair;
}
