#include "core.h"

Core::Core()
{
    objects = new QVector<Object3D*>();
}


void Core::addObject(Object3D *value){
    this->objects->append(value);
}

QVector<Object3D *> *Core::getObjects() const
{
    return objects;
}

void Core::setObjects(QVector<Object3D *> *value)
{
    objects = value;
}
