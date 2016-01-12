#ifndef DRAWBOX_H
#define DRAWBOX_H

#include <GL/glut.h>
#include <QDebug>
#include <math.h>
#include "cuboid.h"

class DrawBox
{
private:
    double width;
    double height;
    double depth;
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
    DrawBox();
    DrawBox(double width, double height, double depth,
            double r, double p, double yy,
            double x, double y, double z,
            double red, double green, double blue, double alpha);
    void drawBox(double xc, double yc, double zc);
};

#endif // DRAWBOX_H
