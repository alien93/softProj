#include "collision.h"

QString Collision::getName() const
{
    return name;
}

void Collision::setName(const QString &value)
{
    name = value;
}

Origin Collision::getOrigin() const
{
    return origin;
}

void Collision::setOrigin(const Origin &value)
{
    origin = value;
}

Geometry Collision::getGeometry() const
{
    return geometry;
}

void Collision::setGeometry(const Geometry &value)
{
    geometry = value;
}

Collision::Collision()
{
    
}

Collision::Collision(QString name, Origin origin, Geometry geometry)
{
    this->name = name;
    this->origin = origin;
    this->geometry = geometry;
}
