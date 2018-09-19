#ifndef CORE_H
#define CORE_H
#include <qvector.h>
#include <ObjectClasses/object3d.h>

class Core
{
public:
    Core();

    void addObject(Object3D *value);
    QVector<Object3D *> *getObjects() const;
    void setObjects(QVector<Object3D *> *value);

private:
    QVector<Object3D*> *objects;
};

#endif // CORE_H
