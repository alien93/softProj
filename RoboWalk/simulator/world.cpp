#include "world.h"

#define CAMERA_COLLIDE_BITS 10
#define RAY_COLLIDE_BITS 20

static dWorldID globalWorldID;
static dJointGroupID globalJointGroupID;
static dReal globalRayIntersectionDepth = -1;
static dGeomID ground;

static void nearCallback(void *data, dGeomID o1, dGeomID o2)
{

    /*dBodyID b1 = dGeomGetBody(o1);
    dBodyID b2 = dGeomGetBody(o2);

    if(b1 && b2 && dAreConnectedExcluding(b1, b2, dJointTypeContact))
        return;

    dContact contact[MAX_CONTACTS];

    for(int i=0; i<MAX_CONTACTS; i++)
    {
        contact[i].surface.mode = dContactBounce | dContactSoftCFM;
        contact[i].surface.mu = dInfinity;
        contact[i].surface.mu2 = 0;
        contact[i].surface.bounce = 0.1;
        contact[i].surface.bounce_vel = 0.1;
        contact[i].surface.soft_cfm = 0.01;
    }

    if(int numc = dCollide (o1, o2, MAX_CONTACTS, &contact[0].geom, sizeof(dContact)))
    {
        for (int i=0; i<numc; i++) {
            dJointID c = dJointCreateContact (globalWorldID,globalJointGroupID,contact+i);
            dJointAttach (c,b1,b2);
        }

    }*/
   int i,n;

    // only collide things with the ground
    int g1 = (o1 == ground);
    int g2 = (o2 == ground);
    if (!(g1 ^ g2)) return;

    const int N = 10;
    dContact contact[N];
    n = dCollide (o1,o2,N,&contact[0].geom,sizeof(dContact));
    if (n > 0) {
        qDebug()<<"collision";
      for (i=0; i<n; i++) {
        contact[i].surface.mode = dContactSlip1 | dContactSlip2 |
      dContactSoftERP | dContactSoftCFM | dContactApprox1;
        contact[i].surface.mu = dInfinity;
        contact[i].surface.slip1 = 0.1;
        contact[i].surface.slip2 = 0.1;
        contact[i].surface.soft_erp = 0.5;
        contact[i].surface.soft_cfm = 0.01;
        dJointID c = dJointCreateContact (globalWorldID,globalJointGroupID,&contact[i]);
        dJointAttach (c,
              dGeomGetBody(contact[i].geom.g1),
              dGeomGetBody(contact[i].geom.g2));
      }
    }
}

World::World(dReal gravity)
{
    dInitODE2(0);
    dAllocateODEDataForThread(dAllocateMaskAll);
    worldID = dWorldCreate();                   //creates a new, empty world
    dWorldSetGravity(worldID, 0, 0, gravity);   //0,0,-9.81
    spaceID = dHashSpaceCreate(0);
    jointGroupID = dJointGroupCreate(0);

    ground = dCreatePlane(spaceID, 0, 0, 1, 0);

    dWorldSetERP(worldID, (dReal)0.1);  //controls how much error correction is performed in each time step

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
    dWorldStep(worldID, 0.01);
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



