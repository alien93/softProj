#include "box.h"

double Box::getHeight() const
{
    return height;
}

void Box::setHeight(double value)
{
    height = value;
}

double Box::getWidth() const
{
    return width;
}

void Box::setWidth(double value)
{
    width = value;
}

double Box::getDepth() const
{
    return depth;
}

void Box::setDepth(double value)
{
    depth = value;
}

Box::Box()
{
    
}

Box::Box(double height, double width, double depth)
{
    this->height = height;
    this->width = width;
    this->depth = depth;
}
