#ifndef CUBOID_H
#define CUBOID_H

#include <GL/glut.h>
#include <QDebug>
#include <math.h>

class Cuboid
{
private:
    double width;
    double height;
    double depth;
public:
    Cuboid();
    Cuboid(double width, double height, double depth);
    void drawCuboid();
};

#endif // CUBOID_H
