#ifndef DRAWCYLINDER_H
#define DRAWCYLINDER_H

#include <GL/glut.h>
#include <QDebug>
#include <math.h>
#include "objectode.h"
#include "world.h"

class DrawCylinder:public ObjectODE
{
private:
    double length;
    double radius;
    double r;
    double p;
    double yy;
    double x;
    double y;
    double z;
    double red;
    double green;
    double blue;
    double alpha;
    void rotateMe(double r, double p, double y);
    double convertRadToDegrees(double value);
public:
    DrawCylinder(World* world, bool body, double length, double radius,
                 double r, double p, double yy,
                 double x, double y, double z,
                 double red, double green, double blue, double alpha);
    void draw();
    ~DrawCylinder();

};

#endif // DRAWCYLINDER_H
