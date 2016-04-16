#ifndef PHYSICS_H
#define PHYSICS_H

#include <ode/ode.h>
#include <math.h>
#include <QString>
#include "drawbox.h"
#include "model/link.h"
#include "model/joint.h"
#include "drawbox.h"
#include "drawsphere.h"
#include "drawcylinder.h"
#include <assert.h>


#define DENSITY 1
#define NUM_OBJECTS 1   //maximum number of objects
#define MAX_CONTACTS 32

typedef struct Object
{
    dBodyID body;  //the body
    dGeomID geom;  //geometries representing this body
} Object;

typedef struct MyColor
{
    double red;
    double green;
    double blue;
    double alpha;
}MyColor;


class Physics
{
private:
    int counter;        //geoms counter
    int NUM_BODIES;             // number of bodies/geometries per body
    int NUM_JOINTS;     //number of joints
    map<int, MyColor> colors;
    vector<QString> usedLinks;
    map<QString, Object> objects;
public:
    Physics();
    void odeInit();
    void odeCreateObject(Link l, int linkNum, Origin orig, Axis axis);
    void odeCreateObject(Link l, int linkNum);
    void odeCreateJoint(Joint j, Link parent, Link child, int jointNum, int linksNum);
    void odeDraw(dGeomID g, int count);
    void odeLoop();
    void odeClose();
    double convertRadToDegrees(double value);
};

#endif // PHYSICS_H
