#include "axis.h"

double Axis::getR() const
{
    return r;
}

void Axis::setR(double value)
{
    r = value;
}

double Axis::getP() const
{
    return p;
}

void Axis::setP(double value)
{
    p = value;
}

double Axis::getYy() const
{
    return yy;
}

void Axis::setYy(double value)
{
    yy = value;
}

Axis::Axis():x(1), y(0), z(0), r(0), p(0), yy(0)
{

}

Axis::Axis(double x, double y, double z, double r, double p, double yy):x(1), y(0), z(0), r(0), p(0), yy(0)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->r = r;
    this->p = p;
    this->yy = yy;
}

double Axis::getX() const
{
    return x;
}

void Axis::setX(double value)
{
    x = value;
}

double Axis::getY() const
{
    return y;
}

void Axis::setY(double value)
{
    y = value;
}

double Axis::getZ() const
{
    return z;
}

void Axis::setZ(double value)
{
    z = value;
}


