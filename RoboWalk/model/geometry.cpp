#include "geometry.h"

AbstractObject Geometry::getObject() const
{
    return object;
}

void Geometry::setObject(const AbstractObject &value)
{
    object = value;
}

Geometry::Geometry()
{
    
}

Geometry::Geometry(AbstractObject object)
{
    this->object = object;
}
