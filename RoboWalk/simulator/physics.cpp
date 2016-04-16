#include "physics.h"

#define dDOUBLE

static dWorldID world;
static dSpaceID space;
static Object object[100];
static dJointID joint[100];
static dGeomID ground;
static dJointGroupID jointGroup;

//called by dSpaceCollide when two objects are potentionally colliding
static void nearCallback (void *data, dGeomID o1, dGeomID o2)
{

    //bodies connected by joint, exit
   /* dBodyID b1 = dGeomGetBody(o1);
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
            dJointID c = dJointCreateContact (world,jointGroup,contact+i);
            dJointAttach (c,b1,b2);
        }

    }*/
    // only collide things with the ground
    /* int g1 = (o1 == ground);
     int g2 = (o2 == ground);
     if (!(g1 ^ g2)) return;

     dContact contact[MAX_CONTACTS];
     int n = dCollide (o1,o2,MAX_CONTACTS,&contact[0].geom,sizeof(dContact));
     if (n > 0) {
       for (int i=0; i<n; i++) {
         contact[i].surface.mode = dContactSlip1 | dContactSlip2 |
       dContactSoftERP | dContactSoftCFM | dContactApprox1;
         contact[i].surface.mu = dInfinity;
         contact[i].surface.slip1 = 0.1;
         contact[i].surface.slip2 = 0.1;
         contact[i].surface.soft_erp = 0.5;
         contact[i].surface.soft_cfm = 0.3;
         dJointID c = dJointCreateContact (world,jointGroup,&contact[i]);
         dJointAttach (c,
               dGeomGetBody(contact[i].geom.g1),
               dGeomGetBody(contact[i].geom.g2));
       }
     }*/

     assert(o1);
     assert(o2);

     if(dGeomIsSpace(o1) || dGeomIsSpace(o2))
     {
         dSpaceCollide2(o1, o2, data, &nearCallback);
         return;
     }

     dContact contact[MAX_CONTACTS];
     int n = dCollide(o1, o2, MAX_CONTACTS, &(contact[0].geom), sizeof(dContact));

     if(n>0)
     {
         for(int i=0; i<n; i++)
         {
             contact[i].surface.mode = 0;
             contact[i].surface.mu = 50.0;
             dJointID c = dJointCreateContact(world, jointGroup, &contact[i]);
             dJointAttach(c, dGeomGetBody(contact[i].geom.g1), dGeomGetBody(contact[i].geom.g2));
         }
     }


}


Physics::Physics()
{
    counter = -1;
}

void Physics::odeInit()
{
    dInitODE();
    dAllocateODEDataForThread(dAllocateMaskAll);
    world = dWorldCreate();
    space = dHashSpaceCreate(0);
    jointGroup = dJointGroupCreate(0);
    ground = dCreatePlane(space, 0, 1, 0, 0);
    dWorldSetGravity(world, 0, -1.0, 0);
    dWorldSetContactMaxCorrectingVel(world, 0.2);
    dWorldSetContactSurfaceLayer(world, 0.01);
    dWorldSetAutoDisableFlag(world, 1);
}

void Physics::odeCreateObject(Link l, int linkNum)
{
    //counter = 0;
    NUM_BODIES = linkNum;

    if(std::find(usedLinks.begin(), usedLinks.end(), l.getName())!=usedLinks.end())
    {
        //link has already been used
    }
    else
    {
        usedLinks.push_back(l.getName());

        vector<Visual> visuals = l.getVisual();
        if(visuals.size()>0)
        {
            for(vector<Visual>::iterator it=visuals.begin(); it!=visuals.end(); it++)
            {
                if(counter<NUM_BODIES)
                    counter++;
                else
                    break;


                Origin o = it->getOrigin();
                Geometry g = it->getGeometry();
                Material m = it->getMaterial();


                if(g.getObject().getName() == "cylinder")
                {
                    double length = g.getObject().getLength();
                    double radius = g.getObject().getRadius();
                    double r = o.getRpy_r();
                    double p = o.getRpy_p();
                    double yy = o.getRpy_y();
                    double x = o.getXyz_x();
                    double y = o.getXyz_y();
                    double z = o.getXyz_z();
                    double red = m.getColor().getRed();
                    double green = m.getColor().getGreen();
                    double blue = m.getColor().getBlue();
                    double alpha = m.getColor().getAlpha();

                    //create object
                    object[counter].body = dBodyCreate(world);
                    //set position
                    dBodySetPosition(object[counter].body, x, y, z );
                    //set mass
                    dMass mass;
                    mass.c[0] = x;
                    mass.c[1] = y;
                    mass.c[2] = z;
                    dMassSetCylinder(&mass, DENSITY, 2, radius, length); //1=x, 2=y, 3=z
                    dBodySetMass(object[counter].body, &mass);
                    //set rotation
                    dMatrix3 R;
                    dRFromEulerAngles(R, convertRadToDegrees(r), convertRadToDegrees(p), convertRadToDegrees(yy));
                    dBodySetRotation(object[counter].body, R);
                    //set shape
                    object[counter].geom = dCreateCylinder(space, radius, length);
                    //set geom
                    dGeomSetBody(object[counter].geom, object[counter].body);
                    //set color
                    MyColor c;
                    c.red = red;
                    c.green = green;
                    c.blue = blue;
                    c.alpha = alpha;
                    colors[counter] = c;
                    objects[l.getName()] = object[counter];
                }
                else if(g.getObject().getName() == "box")
                {
                    double width = g.getObject().getWidth();
                    double height = g.getObject().getHeight();
                    double depth = g.getObject().getDepth();
                    double r = o.getRpy_r();
                    double p = o.getRpy_p();
                    double yy = o.getRpy_y();
                    double x = o.getXyz_x();
                    double y = o.getXyz_y();
                    double z = o.getXyz_z();
                    double red = m.getColor().getRed();
                    double green = m.getColor().getGreen();
                    double blue = m.getColor().getBlue();
                    double alpha = m.getColor().getAlpha();

                    //create object
                    object[counter].body = dBodyCreate(world);
                    //set position
                    dBodySetPosition(object[counter].body, x, y, z );
                    //set mass
                    dMass mass;
                    dMassSetBox(&mass, DENSITY, width, height, depth);
                    dBodySetMass(object[counter].body, &mass);
                    //set rotation
                    dMatrix3 R;
                    dRFromEulerAngles(R, convertRadToDegrees(r), convertRadToDegrees(p), convertRadToDegrees(yy));
                    dBodySetRotation(object[counter].body, R);
                    //set shape
                    object[counter].geom = dCreateBox(space, width, height, depth);
                    //set geom
                    dGeomSetBody(object[counter].geom, object[counter].body);
                    //set color
                    MyColor c;
                    c.red = red;
                    c.green = green;
                    c.blue = blue;
                    c.alpha = alpha;
                    colors[counter] = c;
                    objects[l.getName()] = object[counter];
                }
                else if(g.getObject().getName() == "sphere")
                {
                    double radius = g.getObject().getSphereRadius();
                    double r = o.getRpy_r();
                    double p = o.getRpy_p();
                    double yy = o.getRpy_y();
                    double x = o.getXyz_x();
                    double y = o.getXyz_y();
                    double z = o.getXyz_z();
                    double red = m.getColor().getRed();
                    double green = m.getColor().getGreen();
                    double blue = m.getColor().getBlue();
                    double alpha = m.getColor().getAlpha();


                    //create object
                    object[counter].body = dBodyCreate(world);
                    //set position
                    dBodySetPosition(object[counter].body, x, y, z );
                    //set mass
                    dMass mass;
                    dMassSetSphere(&mass, DENSITY, radius);
                    dBodySetMass(object[counter].body, &mass);
                    //set rotation
                    dMatrix3 R;
                    dRFromEulerAngles(R, convertRadToDegrees(r), convertRadToDegrees(p), convertRadToDegrees(yy));
                    dBodySetRotation(object[counter].body, R);
                    //set shape
                    object[counter].geom = dCreateSphere(space, radius);
                    //set geom
                    dGeomSetBody(object[counter].geom, object[counter].body);
                    //set color
                    MyColor c;
                    c.red = red;
                    c.green = green;
                    c.blue = blue;
                    c.alpha = alpha;
                    colors[counter] = c;
                    objects[l.getName()] = object[counter];
                }
            }
        }
    }
}

void Physics::odeCreateObject(Link l, int linkNum, Origin orig, Axis axis)
{
    //counter = 0;
    NUM_BODIES = linkNum;

    if(std::find(usedLinks.begin(), usedLinks.end(), l.getName())!=usedLinks.end())
    {
        //link has already been used
    }
    else
    {
        usedLinks.push_back(l.getName());

        vector<Visual> visuals = l.getVisual();
        if(visuals.size()>0)
        {
            for(vector<Visual>::iterator it=visuals.begin(); it!=visuals.end(); it++)
            {
                if(counter<NUM_BODIES)
                    counter++;
                else
                    break;


                Origin o = it->getOrigin();
                Geometry g = it->getGeometry();
                Material m = it->getMaterial();


                if(g.getObject().getName() == "cylinder")
                {
                    double length = g.getObject().getLength();
                    double radius = g.getObject().getRadius();
                    double r = o.getRpy_r();
                    double p = o.getRpy_p();
                    double yy = o.getRpy_y();
                    double x = o.getXyz_x();
                    double y = o.getXyz_y();
                    double z = o.getXyz_z();
                    double red = m.getColor().getRed();
                    double green = m.getColor().getGreen();
                    double blue = m.getColor().getBlue();
                    double alpha = m.getColor().getAlpha();

                    //create object
                    object[counter].body = dBodyCreate(world);
                    //set position
                    dBodySetPosition(object[counter].body, x + orig.getXyz_x(), y + orig.getXyz_y(), z+orig.getXyz_z() );
                    //set mass
                    dMass mass;
                    dMassSetCylinder(&mass, DENSITY, 2, radius, length); //1=x, 2=y, 3=z
                    dBodySetMass(object[counter].body, &mass);
                    //set rotation
                    dMatrix3 R;
                    dRFromEulerAngles(R, convertRadToDegrees(r) + .1*(axis.getX()),
                                         convertRadToDegrees(p) + .1*(axis.getY()),
                                         convertRadToDegrees(yy) + .1*(axis.getZ()));
                    dBodySetRotation(object[counter].body, R);
                    //set shape
                    object[counter].geom = dCreateCylinder(space, radius, length);
                    //set geom
                    dGeomSetBody(object[counter].geom, object[counter].body);
                    //set color
                    MyColor c;
                    c.red = red;
                    c.green = green;
                    c.blue = blue;
                    c.alpha = alpha;
                    colors[counter] = c;
                    objects[l.getName()] = object[counter];
                }
                else if(g.getObject().getName() == "box")
                {
                    double width = g.getObject().getWidth();
                    double height = g.getObject().getHeight();
                    double depth = g.getObject().getDepth();
                    double r = o.getRpy_r();
                    double p = o.getRpy_p();
                    double yy = o.getRpy_y();
                    double x = o.getXyz_x();
                    double y = o.getXyz_y();
                    double z = o.getXyz_z();
                    double red = m.getColor().getRed();
                    double green = m.getColor().getGreen();
                    double blue = m.getColor().getBlue();
                    double alpha = m.getColor().getAlpha();

                    //create object
                    object[counter].body = dBodyCreate(world);
                    //set position
                    dBodySetPosition(object[counter].body, x + orig.getXyz_x(), y + orig.getXyz_y(), z+orig.getXyz_z() );
                    //set mass
                    dMass mass;
                    dMassSetBox(&mass, DENSITY, width, height, depth);
                    dBodySetMass(object[counter].body, &mass);
                    //set rotation
                    dMatrix3 R;
                    dRFromEulerAngles(R, convertRadToDegrees(r) + .1*(axis.getX()),
                                         convertRadToDegrees(p) + .1*(axis.getY()),
                                         convertRadToDegrees(yy) + .1*(axis.getZ()));
                    dBodySetRotation(object[counter].body, R);
                    //set shape
                    object[counter].geom = dCreateBox(space, width, height, depth);
                    //set geom
                    dGeomSetBody(object[counter].geom, object[counter].body);
                    //set color
                    MyColor c;
                    c.red = red;
                    c.green = green;
                    c.blue = blue;
                    c.alpha = alpha;
                    colors[counter] = c;
                    objects[l.getName()] = object[counter];
                }
                else if(g.getObject().getName() == "sphere")
                {
                    double radius = g.getObject().getSphereRadius();
                    double r = o.getRpy_r();
                    double p = o.getRpy_p();
                    double yy = o.getRpy_y();
                    double x = o.getXyz_x();
                    double y = o.getXyz_y();
                    double z = o.getXyz_z();
                    double red = m.getColor().getRed();
                    double green = m.getColor().getGreen();
                    double blue = m.getColor().getBlue();
                    double alpha = m.getColor().getAlpha();


                    //create object
                    object[counter].body = dBodyCreate(world);
                    //set position
                    dBodySetPosition(object[counter].body, x + orig.getXyz_x(), y + orig.getXyz_y(), z+orig.getXyz_z() );
                    //set mass
                    dMass mass;
                    dMassSetSphere(&mass, DENSITY, radius);
                    dBodySetMass(object[counter].body, &mass);
                    //set rotation
                    dMatrix3 R;
                    dRFromEulerAngles(R, convertRadToDegrees(r) + .1*(axis.getX()),
                                         convertRadToDegrees(p) + .1*(axis.getY()),
                                         convertRadToDegrees(yy) + .1*(axis.getZ()));
                    dBodySetRotation(object[counter].body, R);
                    //set shape
                    object[counter].geom = dCreateSphere(space, radius);
                    //set geom
                    dGeomSetBody(object[counter].geom, object[counter].body);
                    //set color
                    MyColor c;
                    c.red = red;
                    c.green = green;
                    c.blue = blue;
                    c.alpha = alpha;
                    colors[counter] = c;
                    objects[l.getName()] = object[counter];
                }
            }
        }
    }
}

void Physics::odeCreateJoint(Joint j, Link parent, Link child, int jointNum, int linksNum)
{
    NUM_JOINTS = jointNum;

        //odeCreateObject(parent, linksNum);
        //odeCreateObject(child, linksNum);

        for(int i=0; i<NUM_JOINTS; i++)
        {
            joint[i] = dJointCreateHinge2(world, 0);
            Object obj1= objects[parent.getName()];
            Object obj2= objects[child.getName()];
            if(objects.count(parent.getName()) && objects.count(child.getName()))
            {}
            else
            {
            dJointAttach(joint[i], obj1.body, obj2.body);
             const dReal *a = dBodyGetPosition (obj2.body);
            dJointSetBallAnchor(joint[i],j.getOrigin().getXyz_x(), j.getOrigin().getXyz_y(), j.getOrigin().getXyz_z());

           // djointse
           // dJointSetHingeAnchor(joint[i], j.getOrigin().getXyz_x(), j.getOrigin().getXyz_y(), j.getOrigin().getXyz_z());

          //  dJointSetHingeAxis(joint[i], j.getAxis().getX(), j.getAxis().getY(), j.getAxis().getZ());
            //dJointSetHinge2Axis2(joint[i], 0, 0, 1);
            //dJointSetHinge2Param (joint[ia],dParamLoStop,0);
            //dJointSetHinge2Param (joint[i],dParamHiStop,0);
           }
          /*  if(j.getType() == 3)    //fixeed
                dJointSetFixed(joint[i]);*/
        }
}




void Physics::odeDraw(dGeomID g, int count)
{
    if(!g)
        return;
    const dReal* position = dGeomGetPosition(g);
    const dReal* r = dGeomGetRotation(g);
    MyColor c = colors[count];

    qDebug()<<"--------------------------";
    qDebug()<<r[0];
    qDebug()<<r[1];
    qDebug()<<r[2];

    if(dGeomGetClass(g) == dBoxClass)
    {
        dReal sides[3];
        dGeomBoxGetLengths(g, sides);


        //odeDrawLink();
        DrawBox* db = new DrawBox((double)sides[0], (double)sides[1],
                (double)sides[2], (double)r[0], (double)r[1], (double)r[2],
                (double)position[0], (double)position[1], (double)position[2],
                c.red, c.green, c.blue, c.alpha);
        db->drawBox();
    }
    else if(dGeomGetClass(g) == dSphereClass)
    {
        dReal radius = dGeomSphereGetRadius(g);

        DrawSphere* ds = new DrawSphere((double)radius, (double)r[0], (double)r[1], (double)r[2],
                (double)position[0], (double)position[1], (double)position[2],
                c.red, c.green, c.blue, c.alpha);
        ds->drawSphere();

    }
    else if(dGeomGetClass(g) == dCylinderClass)
    {
        dReal radius, lenght;
        dGeomCylinderGetParams(g, &radius, &lenght);

        DrawCylinder* dc = new DrawCylinder((double)lenght, (double)radius, (double)r[0], (double)r[1], (double)r[2],
                (double)position[0], (double)position[1], (double)position[2],
                c.red, c.green, c.blue, c.alpha);
        dc->drawCylinder();

    }
}

void Physics::odeLoop()
{
    dSpaceCollide(space, 0, &nearCallback);
    dWorldQuickStep(world, 0.05);
    //remove all contact joints
    dJointGroupEmpty(jointGroup);
    for(int i=0; i<NUM_BODIES; i++)
    {
        odeDraw(object[i].geom, i);
    }
}



void Physics::odeClose()
{
    dJointGroupDestroy(jointGroup);
    dSpaceDestroy(space);
    dWorldDestroy(world);
}

double Physics::convertRadToDegrees(double value)
{
    double retVal;
    retVal = value * 180 / M_PI;
    return retVal;
}
