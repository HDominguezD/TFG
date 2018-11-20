#ifndef CORE_H
#define CORE_H
#include <QMenu>
#include "objectclasses/abstractclasses/object.h"

class Core
{
public:
    Core();

    void addObject3D(Object *value);
    QVector<Object*>* getObjects3D() const;
    void removeObject3D(Object *value);

    void addObject2D(Object *value);
    QVector<Object*>* getObjects2D() const;
    void removeObject2D(Object *value);

    void addVolObject(Object *value);
    QVector<Object*>* getVolObjects() const;
    void removeVolObject(Object* value);

private:
    QVector<Object*>* objects3D;
    QVector<Object*>* objects2D;
    QVector<Object*>* volObjects;
};

#endif // CORE_H
