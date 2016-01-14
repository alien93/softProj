#ifndef DRAWSPHERE_H
#define DRAWSPHERE_H

#include <GL/glut.h>
#include <QDebug>
#include <math.h>

class DrawSphere
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
    void rotateMe(double r, double p, double y);
    double convertRadToDegrees(double value);
public:
    DrawSphere();
    DrawSphere( double radius,
                 double r, double p, double yy,
                 double x, double y, double z,
                 double red, double green, double blue, double alpha);
    void drawSphere();
};

#endif // DRAWSPHERE_H
