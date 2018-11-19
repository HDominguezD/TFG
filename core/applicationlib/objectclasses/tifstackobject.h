#ifndef TIFSTACKOBJECT_H
#define TIFSTACKOBJECT_H
#include "abstractclasses/object.h"
#include "tifobject.h"

class TifStackObject : public Object
{
public:
    TifStackObject();
    bool readObject();
    void printObject(QVTKWidget * widget);
    const char* objectType();

    QVector<TifObject *> *getTifStack() const;
    void setTifStack(QVector<TifObject *> *value);
    void addTifObject(TifObject* value);
    void removeTifObject(TifObject* value);

    int getActiveImage() const;
    void setActiveImage(int value);

private:
    bool readObjectFromFile(std::string fileName);
    QVector<TifObject*> *tifStack;
    int activeImage;
};

#endif // TIFSTACKOBJECT_H
