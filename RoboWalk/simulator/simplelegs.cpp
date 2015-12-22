#include "simplelegs.h"
#include <GL/glut.h>

SimpleLegs::SimpleLegs()
{

}

void SimpleLegs::drawLegs()
{
    glColor3ub(255,0,0);
    glutSolidTeapot(.3);
}


