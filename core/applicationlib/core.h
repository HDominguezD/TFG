#ifndef CORE_H
#define CORE_H
#include <QtWidgets/qmenu.h>
#include "objectclasses/abstractclasses/object.h"
#include <QVTKWidget.h>
#include <QDockWidget>

class Core
{
public:
    Core();

    void addObject(Object *value);
    QVector<Object*>* getObjects() const;
    void removeObject(Object* value);

    void addTab(QDockWidget *value);
    QVector<QDockWidget*>* getTabs() const;
    void removeTab(QDockWidget* value);

private:
    QVector<Object*>* objects;
    QVector<QDockWidget*>* tabs;
};

#endif // CORE_H
