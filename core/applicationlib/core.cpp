#include "core.h"

Core::Core()
{
    objects3D = new QVector<Object*>();
    objects2D = new QVector<Object*>();
    volObjects = new QVector<Object*>();
}

void Core::addObject3D(Object *value)
{
    if(strcmp(value->objectType(), "obj") == 0)
        this->objects3D->append(value);
}

QVector<Object *> *Core::getObjects3D() const
{
    return objects3D;
}

void Core::removeObject3D(Object *value)
{
    this->objects3D->removeOne(value);
}

void Core::addObject2D(Object *value)
{
    if(strcmp(value->objectType(), "tif") == 0)
        this->objects2D->append(value);
}

QVector<Object *> *Core::getObjects2D() const
{
    return objects2D;
}

void Core::removeObject2D(Object *value)
{
    this->objects2D->removeOne(value);
}

void Core::addVolObject(Object *value)
{
    if(strcmp(value->objectType(), "tifSlides") == 0)
        this->volObjects->append(value);
}

QVector<Object *> * Core::getVolObjects() const
{
    return this->volObjects;
}

void Core::removeVolObject(Object * value)
{
    this->volObjects->removeOne(value);
}
