#ifndef CORE_H
#define CORE_H
#include <qvector.h>
#include <ObjectClasses/object3d.h>

class Core
{
public:
    Core();
    QVector<Object3D> getObjects() const;
    void setObjects(const QVector<Object3D> &value);

private:
    QVector<Object3D> objects;
};

#endif // CORE_H
