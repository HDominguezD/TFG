#ifndef OBJECTTREEWIDGETITEM_H
#define OBJECTTREEWIDGETITEM_H

#include "QTreeWidgetItem"
#include "Pairs/objectpropertiespair.h"

class ObjectTreeWidgetItem : public QTreeWidgetItem
{
public:
    ObjectTreeWidgetItem(ObjectPropertiesPair *objectPropertiesPair);
    ObjectPropertiesPair *getObjectPropertiesPair() const;

private:
    ObjectPropertiesPair *objectPropertiesPair;
};

#endif // OBJECTTREEWIDGETITEM_H
