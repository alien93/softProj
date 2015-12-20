#include "dynamics.h"

double Dynamics::getDamping() const
{
    return damping;
}

void Dynamics::setDamping(double value)
{
    damping = value;
}

double Dynamics::getFriction() const
{
    return friction;
}

void Dynamics::setFriction(double value)
{
    friction = value;
}

Dynamics::Dynamics()
{
    
}

Dynamics::Dynamics (double damping, double friction)
{
    this->damping = damping;
    this->friction = friction;
}
