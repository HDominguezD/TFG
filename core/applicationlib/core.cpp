#include "core.h"

Core::Core()
{
    objects = new QVector<Object*>();
    tabs = new QVector<QWidget*>();
}

void Core::addObject(Object *value)
{
    this->objects->append(value);
}

QVector<Object *> *Core::getObjects() const
{
    return objects;
}

void Core::removeObject(Object *value)
{
    this->objects->removeOne(value);
}

void Core::addTab(QWidget *value)
{
    this->tabs->append(value);
}

QVector<QWidget*> *Core::getTabs() const
{
    return tabs;
}

void Core::removeTab(QWidget *value)
{
    this->tabs->removeOne(value);
}
