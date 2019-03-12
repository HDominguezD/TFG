#ifndef OBJECTPROPERTIESPAIR_H
#define OBJECTPROPERTIESPAIR_H

#include "objectclasses/abstractclasses/object.h"
#include "QDockWidget"

class ObjectPropertiesPair
{
public:
    ObjectPropertiesPair(Object *object, QDockWidget *propertiesDock);

    Object *getObject() const;
    void setObject(Object *value);

    QDockWidget *getPropertiesDock() const;
    void setPropertiesDock(QDockWidget *value);

private:
    Object *object;
    QDockWidget *propertiesDock;
};

#endif // OBJECTPROPERTIESPAIR_H
