#include "link.h"

Link::Link()
{

}

Link::Link(QString name, Inertial inertial, Visual visual, Collision collision)
{
    this->name = name;
    this->inertial = inertial;
    this->visual = visual;
    this->collision = collision;
}

QString Link::getName() const
{
    return name;
}

void Link::setName(const QString &value)
{
    name = value;
}

Inertial Link::getInertial() const
{
    return inertial;
}

void Link::setInertial(const Inertial &value)
{
    inertial = value;
}

Visual Link::getVisual() const
{
    return visual;
}

void Link::setVisual(const Visual &value)
{
    visual = value;
}

Collision Link::getCollision() const
{
    return collision;
}

void Link::setCollision(const Collision &value)
{
    collision = value;
}



