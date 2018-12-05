#ifndef CORE_H
#define CORE_H
#include <QtWidgets/qmenu.h>
#include "objectclasses/abstractclasses/object.h"
#include <QVTKWidget.h>

class Core
{
public:
    Core();

    void addObject(Object *value);
    QVector<Object*>* getObjects() const;
    void removeObject(Object* value);

    void addTab(QWidget *value);
    QVector<QWidget*>* getTabs() const;
    void removeTab(QWidget* value);

private:
    QVector<Object*>* objects;
    QVector<QWidget*>* tabs;
};

#endif // CORE_H
