#include "world.h"


World::World(dReal gravity)
{
    worldID = dWorldCreate();   //creates a new, empty world
    dWorldSetGravity(worldID, 0, gravity, 0);   //0,0,-9.81
    spaceID = dSimpleSpaceCreate(0);
    jointGroupID = dJointGroupCreate(0);
    dWorldSetERP(worldID, (dReal)0.5);  //controls how much error correction is performed in each time step
}

World::~World()
{
    dWorldDestroy(worldID);
    dJointGroupDestroy(jointGroupID);
    dCloseODE();
}
