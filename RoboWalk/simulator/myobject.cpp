#include "myobject.h"

MyObject::MyObject(bool ObjectODE, dReal posX, dReal posY, dReal posZ)
{
    position.x = posX;
    position.y = posY;
    position.z = posZ;
    objectODE = ObjectODE;
}


MyObject::~MyObject()
{

}

void MyObject::setPosition(Point3 newPosition)
{

}

Point3 MyObject::getPosition()
{
    return position;
}

void MyObject::setOrientation(int axis, dReal angle)
{

}

void MyObject::draw()
{

}

bool MyObject::isObjectODE()
{
    return objectODE;
}
