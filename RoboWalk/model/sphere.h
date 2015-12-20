#ifndef SPHERE_H
#define SPHERE_H

#include "abstractobject.h"

class Sphere:public AbstractObject
{
private:
    double radius;
public:
    Sphere();
    Sphere(double radius);


    double getRadius() const;
    void setRadius(double value);
};

#endif // SPHERE_H
