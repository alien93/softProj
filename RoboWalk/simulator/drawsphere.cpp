#include "drawsphere.h"

DrawSphere::DrawSphere()
{
}

DrawSphere::DrawSphere( double radius, double r, double p, double yy, double x, double y, double z, double red, double green, double blue, double alpha)
{
    this->radius = radius;
    this->r = r;
    this->p = p;
    this->yy = yy;
    this->x = x;
    this->y = y;
    this->z = z;
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = alpha;
}

void DrawSphere::drawSphere()
{
    glTranslated(x,z, y);
    rotateMe(r, p, yy);
    glColor4d(red, green, blue, alpha);
    glutSolidSphere(radius, 32, 32);
}

void DrawSphere::rotateMe(double r, double p, double y)
{
    double angle = 0;
    if(r!=0)
    {
        angle = convertRadToDegrees(r);
        r = 1;
    }
     if(p!=0)
    {
        angle = convertRadToDegrees(p);
        p = 1;
    }
     if(y!=0)
    {
        angle = convertRadToDegrees(y);
        y = 1;
    }
    glRotated(angle, r, p, y);
}

double DrawSphere::convertRadToDegrees(double value)
{
    double retVal;
    retVal = value * 180 / M_PI;
    return retVal;
}
