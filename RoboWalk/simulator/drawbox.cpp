#include "drawbox.h"

DrawBox::DrawBox()
{

}

DrawBox::DrawBox(double width, double height, double depth, double r, double p, double yy, double x, double y, double z, double red, double green, double blue, double alpha)
{
    this->width = width;
    this->height = height;
    this->depth = depth;
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

void DrawBox::drawBox()
{
    glPushMatrix();
   // glTranslated(x,z,y);
    rotateMe(r, p, yy);
    glColor4d(red, green, blue, alpha);
    Cuboid c = Cuboid(width, height, depth);
    c.drawCuboid();
    glPopMatrix();
}

void DrawBox::rotateMe(double r, double p, double y)
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

double DrawBox::convertRadToDegrees(double value)
{
    double retVal;
    retVal = value * 180 / M_PI;
    return retVal;
}
