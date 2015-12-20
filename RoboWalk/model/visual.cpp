#include "visual.h"


Visual::Visual()
{

}

Visual::Visual(QString name, Origin origin,
               Geometry geometry, Material material)
{
    this->name = name;
    this->origin = origin;
    this->geometry = geometry;
    this->material = material;
}

QString Visual::getName() const
{
    return name;
}

void Visual::setName(const QString &value)
{
    name = value;
}

Origin Visual::getOrigin() const
{
    return origin;
}

void Visual::setOrigin(const Origin &value)
{
    origin = value;
}

Geometry Visual::getGeometry() const
{
    return geometry;
}

void Visual::setGeometry(const Geometry &value)
{
    geometry = value;
}

Material Visual::getMaterial() const
{
    return material;
}

void Visual::setMaterial(const Material &value)
{
    material = value;
}


