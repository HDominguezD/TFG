#ifndef CORE_H
#define CORE_H
#include <qvector.h>
#include <ObjectClasses/AbstractClasses/object3d.h>
#include <ObjectClasses/AbstractClasses/object2d.h>

class Core
{
public:
    Core();

    void addObject3D(Object3D *value);
    QVector<Object3D *> *getObjects3D() const;
    void removeObject3D(Object3D * value);
    void addObject2D(Object2D *value);
    QVector<Object2D *> *getObjects2D() const;
    void removeObject2D(Object2D * value);

private:
    QVector<Object3D*> *objects3D;
    QVector<Object2D*> *objects2D;
};

#endif // CORE_H
