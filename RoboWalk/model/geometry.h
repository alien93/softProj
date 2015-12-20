#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "abstractobject.h"

class Geometry
{
private:
    AbstractObject object;
public:
    Geometry();
    Geometry(AbstractObject object);


    AbstractObject getObject() const;
    void setObject(const AbstractObject &value);
};

#endif // GEOMETRY_H
