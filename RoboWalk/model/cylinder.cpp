#include "cylinder.h"

double Cylinder::getRadius() const
{
    return radius;
}

void Cylinder::setRadius(double value)
{
    radius = value;
}

double Cylinder::getLength() const
{
    return length;
}

void Cylinder::setLength(double value)
{
    length = value;
}

Cylinder::Cylinder()
{
    
}

Cylinder::Cylinder(double radius, double length)
{
    this->radius = radius;
    this->length = length;
}
