#include "world.h"

#define CAMERA_COLLIDE_BITS 10
#define RAY_COLLIDE_BITS 20

static dWorldID globalWorldID;
static dJointGroupID globalJointGroupID;
static dReal globalRayIntersectionDepth = -1;
static dGeomID ground;

static void nearCallback(void *data, dGeomID o1, dGeomID o2)
{
    if(dGeomIsSpace(o1) || dGeomIsSpace(o2))
    {
        dSpaceCollide2(o1, o2, data, &nearCallback);

        if(dGeomIsSpace(o1))
            dSpaceCollide((dSpaceID)o1, data, &nearCallback);
        if(dGeomIsSpace(o2))
            dSpaceCollide((dSpaceID)o2, data, &nearCallback);
    }
    else
    {
        if((dGeomGetCollideBits(o1) == RAY_COLLIDE_BITS &&
           dGeomGetCollideBits(o2) == CAMERA_COLLIDE_BITS) ||
           (dGeomGetCollideBits(o1) == CAMERA_COLLIDE_BITS &&
           dGeomGetCollideBits(o2) == RAY_COLLIDE_BITS))
            return;
        int numberCP;
        dContactGeom cpArray[MAX_CONTACTS];
        numberCP = dCollide(o1, o2, MAX_CONTACTS, cpArray, sizeof(dContactGeom));
        dBodyID o1_bodyID = dGeomGetBody(o1);
        dBodyID o2_bodyID = dGeomGetBody(o2);

        if(o1_bodyID != 0 && o2_bodyID != 0 &&
           numberCP > 0 && dAreConnectedExcluding(o1_bodyID, o2_bodyID, dJointTypeContact))
                return;

        if(dGeomGetCollideBits(o1) == RAY_COLLIDE_BITS || dGeomGetCollideBits(o2) == RAY_COLLIDE_BITS)
        {
            if(numberCP > 0)
            {
                if(globalRayIntersectionDepth == -1 || cpArray[0].depth < globalRayIntersectionDepth)
                {
                    globalRayIntersectionDepth = cpArray[0].depth;
                }
            }
        }
        else
        {
            for(int i=0; i<numberCP; i++)
            {
                dContact tempContact;
                tempContact.surface.mode = 0;
                tempContact.surface.mu = dInfinity;
                tempContact.geom = cpArray[i];
                dJointID j = dJointCreateContact(globalWorldID, globalJointGroupID, &tempContact);
                dJointAttach(j, dGeomGetBody(o1), dGeomGetBody(o2));  //joint and bodies must be in same world
            }
        }
    }
}

World::World(dReal gravity)
{
    dInitODE2(0);
    dAllocateODEDataForThread(dAllocateMaskAll);
    worldID = dWorldCreate();   //creates a new, empty world
    dWorldSetGravity(worldID, 0, gravity, 0);   //0,0,-9.81
    spaceID = dHashSpaceCreate(0);
    jointGroupID = dJointGroupCreate(0);

    //ground = dCreatePlane(spaceID, 0, 1, 0, 0);

    dWorldSetERP(worldID, (dReal)0.9);  //controls how much error correction is performed in each time step

    globalWorldID = worldID;
    globalJointGroupID = jointGroupID;

}

World::~World()
{
    dJointGroupDestroy(jointGroupID);
    dSpaceDestroy(spaceID);
    dWorldDestroy(worldID);
    dCloseODE();
}


void World::loop()
{
    globalRayIntersectionDepth = -1;
    dSpaceCollide(spaceID, 0, &nearCallback);
    rayIntersectionDepth = globalRayIntersectionDepth;
    //    dWorldStep(worldID, STEP_ITERATIONS);
    dWorldQuickStep(worldID, STEP_ITERATIONS);
    dJointGroupEmpty(jointGroupID);
}

dWorldID World::getWorldID()
{
    return worldID;
}

dSpaceID World::getSpaceID()
{
    return spaceID;
}

dReal World::getRayIntersectionDepth()
{
    return rayIntersectionDepth;
}



