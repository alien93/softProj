#ifndef WORLD_H
#define WORLD_H

#include <ode/ode.h>

class World
{
public:
    dWorldID worldID;   //dynamics world that contains all the simulation data
    dSpaceID spaceID;   //a collision sace, used to organise and speed up collision tests
    dJointGroupID jointGroupID; //a group of joints, makes it easy to destroy all joints at once


    World(dReal gravity);
    ~World();
};

#endif // WORLD_H
