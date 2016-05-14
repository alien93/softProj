#ifndef OBJECTODE_H
#define OBJECTODE_H

#include "myobject.h"
#include <ode/ode.h>
#include "world.h"

#define PI 3.141592
#define	DEG2RAD(x) (((x)*PI)/180.0)
#define	RAD2DEG(x) (((x)*180.0)/PI)

class ObjectODE: public MyObject
{
protected:
    dBodyID bodyID;
    dGeomID geomID;
    bool hasBody;
public:
    ObjectODE(bool body, dReal posX, dReal posY, dReal posZ);
    virtual ~ObjectODE();
    virtual void draw();

    void setPosition(Point3 newPosition);
    Point3 getPosition();

    void setOrientation(int axis, dReal angle);

    void setVelocity(Vector3 velocity);
    Vector3 getVelocity();

    dBodyID getBodyID();
    void setBodyID(dBodyID bodyID);

    dGeomID getGeomID();
    void setGeomID(dGeomID geomID);

    bool isHasBody();


    virtual void rotateRightThigh(double angle);
    virtual void rotateLeftThigh(double angle);
    virtual void rotateRightLowerLeg(double angle);
    virtual void rotateLeftLowerLeg(double angle);
    virtual void rotateRightFoot(double angle);
    virtual void rotateLeftFoot(double angle);
};

#endif // OBJECTODE_H
