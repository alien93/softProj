#ifndef WORLD_H
#define WORLD_H

#include <ode/ode.h>
#include <QDebug>

#define MAX_CONTACTS 32

class World
{
private:
    dWorldID worldID;   //dynamics world that contains all the simulation data
    dSpaceID spaceID;   //a collision space, used to organise and speed up collision tests
    dJointGroupID jointGroupID; //a group of joints, makes it easy to destroy all joints at once
    dReal rayIntersectionDepth;
public:
    dWorldID getWorldID();
    dSpaceID getSpaceID();
    dReal getRayIntersectionDepth();
    void loop();
    World(dReal gravity);
    ~World();
};

#endif // WORLD_H
