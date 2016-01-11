#include "simplelegs.h"
#include <GL/glut.h>

#include "simulator/drawcylinder.h"
SimpleLegs::SimpleLegs()
{

}

void SimpleLegs::drawLegs()
{
    glColor3ub(255,0,0);
    //glutSolidTeapot(.3);
    glutSolidCube(0.4);

}


