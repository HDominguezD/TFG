#include "core.h"

Core::Core()
{
    objects = new QVector<Object*>();
    tabs = new QVector<QDockWidget*>();
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

void Core::addTab(QDockWidget *value)
{
    this->tabs->append(value);
}

QVector<QDockWidget*> *Core::getTabs() const
{
    return tabs;
}

void Core::removeTab(QDockWidget *value)
{
    this->tabs->removeOne(value);
}
