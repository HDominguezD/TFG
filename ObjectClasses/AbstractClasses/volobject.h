#ifndef VOLOBJECT_H
#define VOLOBJECT_H
#include <qvector2d.h>

using namespace std;

class VolObject
{
public:
    virtual bool readObjectFromFile(string fileName) = 0;
    virtual ~VolObject(){}
};

#endif // VOLOBJECT_H
