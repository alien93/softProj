#ifndef SPHERE_H
#define SPHERE_H

#include "abstractobject.h"

class Sphere:public AbstractObject
{
public:
    Sphere();
    Sphere(const AbstractObject& ao):AbstractObject(ao){}
    Sphere(double radius);


    double getRadius() const;
    void setRadius(double value);
};

#endif // SPHERE_H
