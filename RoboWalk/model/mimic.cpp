#include "mimic.h"


Mimic::Mimic():joint(""), multiplier(1), offset(0)
{
    
}

Mimic::Mimic(QString joint, double multiplier, double offset):joint(""), multiplier(1), offset(0)
{
    this->joint = joint;
    this->multiplier = multiplier;
    this->offset = offset;
}

QString Mimic::getJoint() const
{
    return joint;
}

void Mimic::setJoint(const QString &value)
{
    joint = value;
}

double Mimic::getMultiplier() const
{
    return multiplier;
}

void Mimic::setMultiplier(double value)
{
    multiplier = value;
}

double Mimic::getOffset() const
{
    return offset;
}

void Mimic::setOffset(double value)
{
    offset = value;
}

