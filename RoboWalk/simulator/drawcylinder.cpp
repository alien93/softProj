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

    glPushMatrix();
    glTranslated(x, y ,z);
    rotateMe(r, p, yy);
    glColor4d(red, green, blue, alpha);
    GLUquadric* cylinder = gluNewQuadric();
    gluCylinder(cylinder,radius, radius, length, 32, 32);
    gluDisk(cylinder,0,radius, 32, 32);
    glTranslated(0.0,0.0 , length);
    gluDisk(cylinder,0,radius, 32, 32);
    glPopMatrix();
    glPopMatrix();
}

void DrawCylinder::rotateMe(double r, double p, double y)
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
    if(r+p+y>1)
        glRotated(angle, r, p, y);
    glRotated(angle, r, p, y);
    glTranslated(0.0, 0.0, -length/2);

}

double DrawCylinder::convertRadToDegrees(double value)
{
    double retVal;
    retVal = value * 180 / M_PI;
    return retVal;
}
