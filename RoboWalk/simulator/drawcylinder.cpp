#include "drawcylinder.h"


DrawCylinder::DrawCylinder()
{

}
DrawCylinder::DrawCylinder(double length, double radius, double r, double p, double yy, double x, double y, double z, double red, double green, double blue, double alpha)
{
    this->length = length;
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

void DrawCylinder::drawCylinder()
{
    glTranslated(0.0, length/2, 0.0);
    glTranslated(x, y ,z);
    //glTranslated(0.0, 0.0, -length/2);
    rotateMe(r, p, yy);
    glColor4d(red, green, blue, alpha);
    GLUquadric* cylinder = gluNewQuadric();
    gluCylinder(cylinder,radius, radius, length, 32, 32);
    gluDisk(cylinder,0,radius, 32, 32);
    glTranslated(0.0,0.0 , length);
    gluDisk(cylinder,0,radius, 32, 32);
}

void DrawCylinder::rotateMe(double r, double p, double y)
{
    double angle = 0;
    if(r!=0)
    {
        angle = convertRadToDegrees(r);
        r = 1;
    }
    else if(p!=0)
    {
        angle = convertRadToDegrees(p);
        p = 1;
    }
    else if(y!=0)
    {
        angle = convertRadToDegrees(y);
        y = 1;
    }
    glRotated(angle, r, p, y);
}

double DrawCylinder::convertRadToDegrees(double value)
{
    double retVal;
    retVal = value * 180 / M_PI;
    return retVal;
}
