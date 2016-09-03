#ifndef ROBOT_H
#define ROBOT_H

#include <QGLWidget>
#include <QTimer>
#include "drawcylinder.h"
#include "drawsphere.h"
#include "drawbox.h"
#include <vector>
#include "model/visual.h"
#include <array>
#include <ode/ode.h>
#include "objectode.h"
#include "ann/ann.h"
#include "timer.h"
#include "urdfparser.h"
#include <cmath>

class Robot:public ObjectODE
{
private:
    URDFparser *parser;

    GLfloat m[16];
    map<QString, GLfloat[16]> matrices;
    double limit;

    ObjectODE* elem1;   //for joints
    ObjectODE* elem2;
    World *w;

    DrawCylinder *cylinder;
    DrawBox *box;
    DrawSphere *sphere;

public:
    static QString jointName;

    Robot(World* world, dReal posX, dReal posY, dReal posZ);
    ~Robot();

    ObjectODE *draw(Link l);
    void animation();

    void rotateMe(double r, double p, double y);
    double convertRadToDegrees(double value);

    // MyObject interface
public:
    void setPosition(Point3 newPosition);
    Point3 getPosition();
    void setOrientation(int axis, dReal angle);
    void draw();
    double getLimit() const;
    void setLimit(double value);
};

#endif // ROBOT_H
