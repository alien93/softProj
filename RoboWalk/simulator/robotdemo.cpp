#include "robotdemo.h"

RobotDemo::RobotDemo(World *world, dReal posX, dReal posY, dReal posZ, dReal size)
    :ObjectODE(true, posX, posY, posZ)
{
    Point3 jointPosition;



    //body parts dimensions
    Point3 torso_dim = {(dReal)size, (dReal).5*size, (dReal).5*size};
    Point3 upperLeg_dim = {(dReal).4*size, (dReal)1.7*size, (dReal).4*size};
    Point3 lowerLeg_dim = {(dReal).3*size, (dReal)1.7*size, (dReal).3*size};
    Point3 foot_dim = {(dReal)0.3*size, (dReal)0.3*size, (dReal)1.0*size};

    //creating objects
    torso = new DrawBox(world, true, torso_dim.x, torso_dim.y, torso_dim.z, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0);
    l_upperLeg = new DrawBox(world, true, upperLeg_dim.x, upperLeg_dim.y, upperLeg_dim.z, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0);
    r_upperLeg = new DrawBox(world, true, upperLeg_dim.x, upperLeg_dim.y, upperLeg_dim.z, 0, 0, 0, 0, 0, 0, 0, 0.5, 0, 0);
    l_lowerLeg = new DrawBox(world, true, lowerLeg_dim.x, lowerLeg_dim.y, lowerLeg_dim.z, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0);
    r_lowerLeg = new DrawBox(world, true, lowerLeg_dim.x, lowerLeg_dim.y, lowerLeg_dim.z, 0, 0, 0, 0, 0, 0, 0, 0, 0.5, 0);
    l_foot = new DrawBox(world, true, foot_dim.x, foot_dim.y, foot_dim.z, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1);
    r_foot = new DrawBox(world, true, foot_dim.x, foot_dim.y, foot_dim.z, 0, 0, 0, 0, 0, 0, 0, 0, 0.5, 0.5);

    bodyID = torso->getBodyID();
    const dReal* initQ = dBodyGetQuaternion(torso->getBodyID());

    q[0] = initQ[0];
    q[1] = initQ[1];
    q[2] = initQ[2];
    q[3] = initQ[3];

    Point3 startPosition = {posX, posY, posZ};
    setPosition(startPosition);

    //create joints
    //left hip
    l_hip = dJointCreateHinge(world->getWorldID(), 0);
    dJointAttach(l_hip, torso->getBodyID(), l_upperLeg->getBodyID());
    jointPosition = l_upperLeg->getPosition();
    jointPosition.y += l_upperLeg->getHeight()/2;
    dJointSetHingeAnchor(l_hip, jointPosition.x, jointPosition.y, jointPosition.z);
    dJointSetHingeAxis(l_hip, 1, 0, 0);
    dJointSetHingeParam(l_hip, dParamLoStop, -PI/6);
    dJointSetHingeParam(l_hip, dParamHiStop, 3*PI/4);

    //right hip
    r_hip = dJointCreateHinge(world->getWorldID(), 0);
    dJointAttach(r_hip, torso->getBodyID(), r_upperLeg->getBodyID());
    jointPosition = r_upperLeg->getPosition();
    jointPosition.y += r_upperLeg->getHeight()/2;
    dJointSetHingeAnchor(r_hip, jointPosition.x, jointPosition.y, jointPosition.z);
    dJointSetHingeAxis(r_hip, 1, 0, 0);
    dJointSetHingeParam(r_hip, dParamLoStop, -PI/6);
    dJointSetHingeParam(r_hip, dParamHiStop, 3*PI/4);

    //left knee
    l_knee = dJointCreateHinge(world->getWorldID(), 0);
    dJointAttach(l_knee, l_upperLeg->getBodyID(), l_lowerLeg->getBodyID());
    jointPosition = l_upperLeg->getPosition();
    jointPosition.y -= l_upperLeg->getHeight()/2;
    jointPosition.z += l_upperLeg->getDepth()/2;
    dJointSetHingeAnchor(l_knee, jointPosition.x, jointPosition.y, jointPosition.z);
    dJointSetHingeAxis(l_knee, 1, 0, 0);
    dJointSetHingeParam(l_knee, dParamLoStop, -PI/2);
    dJointSetHingeParam(l_knee, dParamHiStop, 0);

    //right knee
    r_knee = dJointCreateHinge(world->getWorldID(), 0);
    dJointAttach(r_knee, r_upperLeg->getBodyID(), r_lowerLeg->getBodyID());
    jointPosition = r_upperLeg->getPosition();
    jointPosition.y -= r_upperLeg->getHeight()/2;
    jointPosition.z += r_upperLeg->getDepth()/2;
    dJointSetHingeAnchor(r_knee, jointPosition.x, jointPosition.y, jointPosition.z);
    dJointSetHingeAxis(r_knee, 1, 0, 0);
    dJointSetHingeParam(r_knee, dParamLoStop, -PI/2);
    dJointSetHingeParam(r_knee, dParamHiStop, 0);

    //left ankle
    l_ankle = dJointCreateHinge(world->getWorldID(), 0);
    dJointAttach(l_ankle, l_lowerLeg->getBodyID(), l_foot->getBodyID());
    jointPosition = l_lowerLeg->getPosition();
    jointPosition.y -= l_lowerLeg->getHeight()/2;
    dJointSetHingeAnchor(l_ankle, jointPosition.x, jointPosition.y, jointPosition.z);
    dJointSetHingeAxis(l_ankle, 1, 0, 0);
    dJointSetHingeParam(l_ankle, dParamLoStop, -PI/2);
    dJointSetHingeParam(l_ankle, dParamHiStop, PI/6);

    //right ankle
    r_ankle = dJointCreateHinge(world->getWorldID(), 0);
    dJointAttach(r_ankle, r_lowerLeg->getBodyID(), r_foot->getBodyID());
    jointPosition = r_lowerLeg->getPosition();
    jointPosition.y -= r_lowerLeg->getHeight()/2;
    dJointSetHingeAnchor(r_ankle, jointPosition.x, jointPosition.y, jointPosition.z);
    dJointSetHingeAxis(r_ankle, 1, 0, 0);
    dJointSetHingeParam(r_ankle, dParamLoStop, -PI/2);
    dJointSetHingeParam(r_ankle, dParamHiStop, PI/6);
}

RobotDemo::~RobotDemo()
{
    dJointDestroy(l_hip);
    dJointDestroy(r_hip);
    dJointDestroy(l_knee);
    dJointDestroy(r_knee);
    dJointDestroy(l_ankle);
    dJointDestroy(r_ankle);
}

void RobotDemo::draw()
{
    l_upperLeg->draw();
    r_upperLeg->draw();
    l_lowerLeg->draw();
    r_lowerLeg->draw();
    l_foot->draw();
    r_foot->draw();
    torso->draw();
}

void RobotDemo::setPosition(Point3 newPosition)
{
    position = newPosition;
    dReal offsetX;
    dReal offsetY;
    dReal offsetZ;

    //torso position
    dBodySetPosition(torso->getBodyID(), position.x, position.y, position.z);
    dBodySetForce(torso->getBodyID(), 0, 0, 0);
    dBodySetLinearVel(torso->getBodyID(), 0, 0, 0);
    dBodySetAngularVel(torso->getBodyID(), 0, 0, 0);
    dBodySetQuaternion(torso->getBodyID(), q);

    //upper leg position
    offsetX = torso->getWidth()/2 - l_upperLeg->getWidth()/2;
    offsetY = -torso->getHeight()/2 - l_upperLeg->getHeight()/2;
    dBodySetPosition(l_upperLeg->getBodyID(), position.x - offsetX, position.y + offsetY, position.z);
    dBodySetPosition(r_upperLeg->getBodyID(), position.x + offsetX, position.y + offsetY, position.z);
    dBodySetForce(l_upperLeg->getBodyID(), 0, 0, 0);
    dBodySetLinearVel(l_upperLeg->getBodyID(), 0, 0, 0);
    dBodySetAngularVel(l_upperLeg->getBodyID(), 0, 0, 0);
    dBodySetQuaternion(l_upperLeg->getBodyID(), q);
    dBodySetForce(r_upperLeg->getBodyID(), 0, 0, 0);
    dBodySetLinearVel(r_upperLeg->getBodyID(), 0, 0, 0);
    dBodySetAngularVel(r_upperLeg->getBodyID(), 0, 0, 0);
    dBodySetQuaternion(r_upperLeg->getBodyID(), q);

    //lower leg position
    offsetX = torso->getWidth()/2 - l_lowerLeg->getWidth()/2;
    offsetY = -torso->getHeight()/2 - l_upperLeg->getHeight() - l_lowerLeg->getHeight()/2;
    dBodySetPosition(l_lowerLeg->getBodyID(), position.x - offsetX, position.y + offsetY, position.z);
    dBodySetPosition(r_lowerLeg->getBodyID(), position.x + offsetX, position.y + offsetY, position.z);
    dBodySetForce(l_lowerLeg->getBodyID(), 0, 0, 0);
    dBodySetLinearVel(l_lowerLeg->getBodyID(), 0, 0, 0);
    dBodySetAngularVel(l_lowerLeg->getBodyID(), 0, 0, 0);
    dBodySetQuaternion(l_lowerLeg->getBodyID(), q);
    dBodySetForce(r_lowerLeg->getBodyID(), 0, 0, 0);
    dBodySetLinearVel(r_lowerLeg->getBodyID(), 0, 0, 0);
    dBodySetAngularVel(r_lowerLeg->getBodyID(), 0, 0, 0);
    dBodySetQuaternion(r_lowerLeg->getBodyID(), q);

    //feet position
    offsetX = torso->getWidth()/2 - l_foot->getWidth()/2;
    offsetY = -torso->getHeight()/2 - l_upperLeg->getHeight() - l_lowerLeg->getHeight() - l_foot->getHeight()/2;
    offsetZ = l_lowerLeg->getDepth()/2;
    dBodySetPosition(l_foot->getBodyID(), position.x - offsetX, position.y + offsetY, position.z + offsetZ);
    dBodySetPosition(r_foot->getBodyID(), position.x + offsetX, position.y + offsetY, position.z + offsetZ);
    dBodySetForce(l_foot->getBodyID(), 0, 0, 0);
    dBodySetLinearVel(l_foot->getBodyID(), 0, 0, 0);
    dBodySetAngularVel(l_foot->getBodyID(), 0, 0, 0);
    dBodySetQuaternion(l_foot->getBodyID(), q);
    dBodySetForce(r_foot->getBodyID(), 0, 0, 0);
    dBodySetLinearVel(r_foot->getBodyID(), 0, 0, 0);
    dBodySetAngularVel(r_foot->getBodyID(), 0, 0, 0);
    dBodySetQuaternion(r_foot->getBodyID(), q);
}

Point3 RobotDemo::getPosition()
{
    const dReal* robotPosition;
    robotPosition = dBodyGetPosition(torso->getBodyID());
    position.x = robotPosition[0];
    position.y = robotPosition[1];
    position.z = robotPosition[2];

    return position;
}

void RobotDemo::setVelocity(Vector3 velocity)
{
    torso->setVelocity(velocity);
    l_upperLeg->setVelocity(velocity);
    r_upperLeg->setVelocity(velocity);
    l_lowerLeg->setVelocity(velocity);
    r_lowerLeg->setVelocity(velocity);
    l_foot->setVelocity(velocity);
    r_foot->setVelocity(velocity);
}
