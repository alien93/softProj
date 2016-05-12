#ifndef ROBOTDEMO_H
#define ROBOTDEMO_H

#include <ode/ode.h>
#include "objectode.h"
#include "world.h"
#include "drawbox.h"

class RobotDemo:public ObjectODE
{
private:
    dQuaternion q;

    DrawBox* torso;
    DrawBox* l_upperLeg;
    DrawBox* r_upperLeg;
    DrawBox* l_lowerLeg;
    DrawBox* r_lowerLeg;
    DrawBox* l_foot;
    DrawBox* r_foot;

    dJointID l_hip;
    dJointID r_hip;
    dJointID l_knee;
    dJointID r_knee;
    dJointID l_ankle;
    dJointID r_ankle;

public:
    RobotDemo(World* world, dReal posX, dReal posY, dReal posZ, dReal size);
    ~RobotDemo();
    void draw();
    void setPosition(Point3 newPosition);
    Point3 getPosition();
    void setVelocity(Vector3 velocity);

    void testRotation();


};

#endif // ROBOTDEMO_H
