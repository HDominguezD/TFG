#include "objecttreewidgetitem.h"

ObjectTreeWidgetItem::ObjectTreeWidgetItem(ObjectPropertiesPair *objectPropertiesPair, QString name)
{
    this->objectPropertiesPair = objectPropertiesPair;
    this->setText(0, name);
}

ObjectPropertiesPair *ObjectTreeWidgetItem::getObjectPropertiesPair() const
{
    return objectPropertiesPair;
}
