#include "axis.h"

Axis::Axis()
{

}

Axis::Axis(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

int Axis::getX() const
{
    return x;
}

void Axis::setX(int value)
{
    x = value;
}

int Axis::getY() const
{
    return y;
}

void Axis::setY(int value)
{
    y = value;
}

int Axis::getZ() const
{
    return z;
}

void Axis::setZ(int value)
{
    z = value;
}


