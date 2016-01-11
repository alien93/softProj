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

void DrawCylinder::drawCylinder(double xc, double yc, double zc)
{
    glPushMatrix();
    glTranslated(xc, yc, zc);
    glTranslated(x,y,z);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    rotateMe(r, p, y);
    glScalef(30, 30, 30);
    glColor4d(red, green, blue, alpha);
    gluCylinder(gluNewQuadric(),radius, radius, length, 32, 32);
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
