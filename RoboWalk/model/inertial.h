#ifndef INERTIAL_H
#define INERTIAL_H


#include "origin.h"
#include "mass.h"
#include "inertia.h"

class Inertial
{
private:
    Origin origin;
    Mass mass;
    Inertia intertia;
public:
    Inertial();
    Inertial(Origin origin, Mass mass, Inertia inertia);

    Origin getOrigin() const;
    void setOrigin(const Origin &value);
    Mass getMass() const;
    void setMass(const Mass &value);
    Inertia getIntertia() const;
    void setIntertia(const Inertia &value);
};

#endif // INERTIAL_H
