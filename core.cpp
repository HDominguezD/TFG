#include "core.h"


Core::Core()
{
    objects3D = new QVector<Object3D*>();
    objects2D = new QVector<Object2D*>();
}


void Core::addObject3D(Object3D *value){
    this->objects3D->append(value);
}

QVector<Object3D *> *Core::getObjects3D() const
{
    return objects3D;
}

void Core::removeObject3D(Object3D *value)
{
    this->objects3D->removeOne(value);
}

void Core::addObject2D(Object2D *value){
    this->objects2D->append(value);
}

QVector<Object2D *> *Core::getObjects2D() const
{
    return objects2D;
}

void Core::removeObject2D(Object2D *value)
{
    this->objects2D->removeOne(value);
}
