#include "abstractobject.h"

QString AbstractObject::getName() const
{
    return name;
}

void AbstractObject::setName(const QString &value)
{
    name = value;
}

AbstractObject::AbstractObject()
{
    this->name = name;
}
