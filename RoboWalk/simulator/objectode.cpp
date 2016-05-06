#include "objectode.h"

ObjectODE::ObjectODE(bool body, dReal posX, dReal posY, dReal posZ)
    :MyObject(true, posX, posY, posZ)
{
    hasBody = body;
}

ObjectODE::~ObjectODE()
{

}

void ObjectODE::setPosition(Point3 newPosition)
{
    position = newPosition;
    dGeomSetPosition(geomID, position.x, position.y, position.z);
}

Point3 ObjectODE::getPosition()
{
    const dReal* geomPosition;
    geomPosition = dGeomGetPosition(geomID);
    position.x = geomPosition[0];
    position.y = geomPosition[1];
    position.z = geomPosition[2];
    return position;
}

void ObjectODE::setOrientation(int axis, dReal angle)
{
    dQuaternion q;

    switch(axis)
    {
        case 0:
                dQFromAxisAndAngle(q, 1, 0, 0, angle);
                break;
        case 1:
                dQFromAxisAndAngle(q, 0, 1, 0, angle);
                break;
        case 2:
                dQFromAxisAndAngle(q, 0, 0, 1, angle);
                break;
        default:
                break;
    }

    dGeomSetQuaternion(geomID, q);
}


void ObjectODE::setVelocity(Vector3 velocity)
{
    if(hasBody)
    {
        dBodySetLinearVel(bodyID, velocity.x, velocity.y, velocity.z);
    }
}

Vector3 ObjectODE::getVelocity()
{
    const dReal* velocity;
    Vector3 newVelocity = {0, 0, 0};

    if(hasBody)
    {
        velocity = dBodyGetLinearVel(bodyID);

        newVelocity.x = velocity[0];
        newVelocity.y = velocity[1];
        newVelocity.z = velocity[2];

        return newVelocity;
    }
    else
    {
        return newVelocity;
    }
}

dBodyID ObjectODE::getBodyID()
{
    return bodyID;
}

void ObjectODE::setBodyID(dBodyID bodyID)
{
    this->bodyID = bodyID;
}

dGeomID ObjectODE::getGeomID()
{
    return geomID;
}

void ObjectODE::setGeomID(dGeomID geomID)
{
    this->geomID = geomID;
}

void ObjectODE::draw()
{}

bool ObjectODE::isHasBody()
{
    return hasBody;
}
