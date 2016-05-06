#ifndef DRAWSPHERE_H
#define DRAWSPHERE_H

#include <GL/glut.h>
#include <QDebug>
#include <math.h>
#include "world.h"
#include <ode/ode.h>
#include "objectode.h"

class DrawSphere:public ObjectODE
{
private:
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
    GLUquadric* quad;
    void rotateMe(double r, double p, double y);
    double convertRadToDegrees(double value);

public:
    DrawSphere(World* world, bool body, double radius,
                 double r, double p, double yy,
                 double x, double y, double z,
                 double red, double green, double blue, double alpha);
    ~DrawSphere();
    void drawSphere();
};

#endif // DRAWSPHERE_H
