#ifndef ROBOTDEMO_H
#define ROBOTDEMO_H

#include <ode/ode.h>
#include "objectode.h"
#include "world.h"
#include "drawbox.h"
#include "drawcylinder.h"

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
    void rotateRightThigh(double angle);
    void rotateRightLowerLeg(double angle);
    void rotateRightFoot(double angle);
    void rotateLeftThigh(double angle);
    void rotateLeftLowerLeg(double angle);
    void rotateLeftFoot(double angle);
    DrawBox *getL_upperLeg() const;
    void setL_upperLeg(DrawBox *value);
    DrawBox *getR_upperLeg() const;
    void setR_upperLeg(DrawBox *value);
    DrawBox *getL_lowerLeg() const;
    void setL_lowerLeg(DrawBox *value);
    DrawBox *getR_lowerLeg() const;
    void setR_lowerLeg(DrawBox *value);
    DrawBox *getL_foot() const;
    void setL_foot(DrawBox *value);
    DrawBox *getR_foot() const;
    void setR_foot(DrawBox *value);
    dJointID getL_hip() const;
    void setL_hip(const dJointID &value);
    dJointID getR_hip() const;
    void setR_hip(const dJointID &value);
    dJointID getL_knee() const;
    void setL_knee(const dJointID &value);
    dJointID getR_knee() const;
    void setR_knee(const dJointID &value);
    dJointID getL_ankle() const;
    void setL_ankle(const dJointID &value);
    dJointID getR_ankle() const;
    void setR_ankle(const dJointID &value);
};

#endif // ROBOTDEMO_H
