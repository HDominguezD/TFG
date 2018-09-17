#include "core.h"

Core::Core()
{

}

QVector<Object3D> Core::getObjects() const
{
    return objects;
}

void Core::setObjects(const QVector<Object3D> &value)
{
    objects = value;
}
