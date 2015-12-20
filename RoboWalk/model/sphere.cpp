#include "sphere.h"

double Sphere::getRadius() const
{
    return radius;
}

void Sphere::setRadius(double value)
{
    radius = value;
}

Sphere::Sphere()
{
    
}

Sphere::Sphere(double radius)
{
    this->radius = radius;
}
