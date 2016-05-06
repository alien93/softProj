#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <ode/ode.h>

#define DEGTORAD 0.01745329251994329577f
#define RADTODEG 57.2957795130823208768f

typedef struct Point3
{
    dReal x, y, z;
}Point3;

typedef struct Vector3
{
    dReal x, y, z;
}Vector3;

class MyObject
{
protected:
    Point3 position;
    bool objectODE;
    Point3 minBox;
    Point3 maxBox;
    Point3 centerBox;
    Point3 modelDimensions;
public:
    MyObject(bool ObjectODE, dReal posX, dReal posY, dReal posZ);
    virtual ~MyObject();
    virtual void setPosition(Point3 newPosition);
    virtual Point3 getPosition();
    virtual void setOrientation(int axis, dReal angle);
    virtual void draw();
    bool isObjectODE();
};

#endif // MYOBJECT_H
