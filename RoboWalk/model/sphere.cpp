#include "sphere.h"

double Sphere::getRadius() const
{
    return radius;
}

void Sphere::setRadius(double value)
{
    sphereRadius = value;
}

Sphere::Sphere()
{
    
}

Sphere::Sphere(double radius)
{
    this->sphereRadius = radius;
}
