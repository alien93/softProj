#include "drawsphere.h"


DrawSphere::DrawSphere(World* world, bool body, double radius, double r, double p, double yy, double x, double y, double z, double red, double green, double blue, double alpha)
    :ObjectODE(body, x, y, z)
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
    quad = gluNewQuadric();

    //ODE
    geomID = dCreateSphere(world->getSpaceID(), radius);

    if(hasBody)
    {
        bodyID = dBodyCreate(world->getWorldID());
        dGeomSetBody(geomID, bodyID);
        dReal newMass = 8*(4.2*pow(radius, 3));
        dMass mass;
        dBodyGetMass(bodyID, &mass);
        dMassAdjust(&mass, newMass);
    }
    else
    {
        dGeomSetBody(geomID, 0);
    }

    Point3 position = {(dReal)x, (dReal)y, (dReal)z};
    setPosition(position);
}

void DrawSphere::drawSphere()
{
<<<<<<< HEAD
    if(hasBody)
    {
        //position
        const dReal* bodyPosition;
        bodyPosition = dBodyGetPosition(bodyID);
        position.x = bodyPosition[0];
        position.y = bodyPosition[1];
        position.z = bodyPosition[2];

        //orientation
        const dReal* R;
        R = dBodyGetRotation(bodyID);

        double m[16];
        m[0] = R[0];
        m[1] = R[4];
        m[2] = R[8];
        m[3] = 0;
        m[4] = R[1];
        m[5] = R[5];
        m[6] = R[9];
        m[7] = 0;
        m[8] = R[2];
        m[9] = R[6];
        m[10] = R[10];
        m[11] = 0;
        m[12] = R[3];
        m[13] = R[7];
        m[14] = R[11];
        m[15] = 1;

        glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glMultMatrixd(m);
        glColor4d(red, green, blue, alpha);
        gluSphere(quad, radius, 32, 32);
        glPopMatrix();
    }
    else
    {
        //position
        const dReal* geomPosition;
        geomPosition = dGeomGetPosition(geomID);
        position.x = geomPosition[0];
        position.y = geomPosition[1];
        position.z = geomPosition[2];

        glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        glColor4d(red, green, blue, alpha);
        gluSphere(quad, radius, 32, 32);
        glPopMatrix();

    }
      /*  glTranslated(x,z, y);
        rotateMe(r, p, yy);
        glColor4d(red, green, blue, alpha);
        //glutSolidSphere(radius, 32, 32);
        gluSphere(quad, radius, 32, 32);*/
=======
        glPushMatrix();
        glTranslated(x,z, y);
        rotateMe(r, p, yy);
        glColor4d(red, green, blue, alpha);
        //glutSolidSphere(radius, 32, 32);
        gluSphere(quad, radius, 32, 32);
        glPopMatrix();
>>>>>>> origin

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

DrawSphere::~DrawSphere()
{
    if(hasBody)
        dBodyDestroy(bodyID);
    gluDeleteQuadric(quad);
}
