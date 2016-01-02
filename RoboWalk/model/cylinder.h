#ifndef CYLINDER_H
#define CYLINDER_H

#include "abstractobject.h"

class Cylinder:public AbstractObject
{
public:
    Cylinder();
    Cylinder(const AbstractObject& ao):AbstractObject(ao){}
    Cylinder(double radius, double length);

    double getRadius() const;
    void setRadius(double value);
    double getLength() const;
    void setLength(double value);
};

#endif // CYLINDER_H
