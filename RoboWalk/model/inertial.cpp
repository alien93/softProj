#include "inertial.h"

Origin Inertial::getOrigin() const
{
    return origin;
}

void Inertial::setOrigin(const Origin &value)
{
    origin = value;
}

Mass Inertial::getMass() const
{
    return mass;
}

void Inertial::setMass(const Mass &value)
{
    mass = value;
}

Inertia Inertial::getIntertia() const
{
    return intertia;
}

void Inertial::setIntertia(const Inertia &value)
{
    intertia = value;
}

Inertial::Inertial()
{
    
}
