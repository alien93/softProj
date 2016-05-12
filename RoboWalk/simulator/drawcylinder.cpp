#include "drawcylinder.h"

DrawCylinder::DrawCylinder(World* world, bool body, double length, double radius, double r, double p, double yy, double x, double y, double z, double red, double green, double blue, double alpha)
    :ObjectODE(body, x, y, z)
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

    //ODE
    geomID = dCreateCylinder(world->getSpaceID(), radius, length);

    if(hasBody)
    {
        bodyID = dBodyCreate(world->getWorldID());
        dBodySetPosition(bodyID, (dReal)x, (dReal)y, (dReal)z);

        dReal newMass = 8*(4.2*pow(radius, 3))*length;
        dMass mass;
        dBodyGetMass(bodyID, &mass);
        dMassAdjust(&mass, newMass);
        dBodySetMass(bodyID, &mass);
        dGeomSetBody(geomID, bodyID);

    }
    else
    {
        dGeomSetBody(geomID, 0);
    }
    Point3 position = {(dReal)x, (dReal)y, (dReal)z};
    setPosition(position);
}

DrawCylinder::~DrawCylinder()
{
    if(hasBody)
        dBodyDestroy(bodyID);
    dGeomDestroy(geomID);
}

void DrawCylinder::draw()
{

    if(hasBody)
    {
        const dReal* bodyPosition;
        bodyPosition = dBodyGetPosition(bodyID);
        position.x = bodyPosition[0];
        position.y = bodyPosition[1];
        position.z = bodyPosition[2];

        // getting orientation
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
        rotateMe(r, p, yy);

        glColor4d(red, green, blue, alpha);
        GLUquadric* cylinder = gluNewQuadric();
        gluCylinder(cylinder,radius, radius, length, 32, 32);
        gluDisk(cylinder,0,radius, 32, 32);
        glTranslated(0.0,0.0 , length);
        gluDisk(cylinder,0,radius, 32, 32);

        glPopMatrix();
    }
    else
    {
        const dReal* geomPosition;
        geomPosition = dGeomGetPosition(geomID);
        position.x = geomPosition[0];
        position.y = geomPosition[1];
        position.z = geomPosition[2];

        glPushMatrix();
        glTranslatef(position.x, position.y, position.z);
        rotateMe(r, p, yy);

        glColor4d(red, green, blue, alpha);
        GLUquadric* cylinder = gluNewQuadric();
        gluCylinder(cylinder,radius, radius, length, 32, 32);
        gluDisk(cylinder,0,radius, 32, 32);
        glTranslated(0.0,0.0 , length);
        gluDisk(cylinder,0,radius, 32, 32);

        glPopMatrix();
    }



  /*  glPushMatrix();
    glTranslated(x, y ,z);
    rotateMe(r, p, yy);
    glColor4d(red, green, blue, alpha);
    GLUquadric* cylinder = gluNewQuadric();
    gluCylinder(cylinder,radius, radius, length, 32, 32);
    gluDisk(cylinder,0,radius, 32, 32);
    glTranslated(0.0,0.0 , length);
    gluDisk(cylinder,0,radius, 32, 32);
    glPopMatrix();
    glPopMatrix();*/
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
