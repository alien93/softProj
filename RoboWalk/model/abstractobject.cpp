#include "abstractobject.h"

QString AbstractObject::getName() const
{
    return name;
}

void AbstractObject::setName(const QString &value)
{
    name = value;
}

double AbstractObject::getHeight() const
{
    return height;
}

void AbstractObject::setHeight(double value)
{
    height = value;
}

double AbstractObject::getWidth() const
{
    return width;
}

void AbstractObject::setWidth(double value)
{
    width = value;
}

double AbstractObject::getDepth() const
{
    return depth;
}

void AbstractObject::setDepth(double value)
{
    depth = value;
}

double AbstractObject::getRadius() const
{
    return radius;
}

void AbstractObject::setRadius(double value)
{
    radius = value;
}

double AbstractObject::getLength() const
{
    return length;
}

void AbstractObject::setLength(double value)
{
    length = value;
}

double AbstractObject::getSphereRadius() const
{
    return sphereRadius;
}

void AbstractObject::setSphereRadius(double value)
{
    sphereRadius = value;
}

AbstractObject::AbstractObject()
{
    this->name = name;
}
