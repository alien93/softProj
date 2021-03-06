#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

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
#include "robotdemo.h"
#include "ann/ann.h"
#include "timer.h"
#include "urdfparser.h"
#include <cmath>
#include "robot.h"

using namespace std;

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
private:
    bool step;
    bool robotLoaded;
    DrawCylinder *cylinder;
    DrawBox *box;
    DrawSphere *sphere;
    URDFparser *parser;

    ObjectODE* elem1;   //for joints
    ObjectODE* elem2;

    ObjectODE* ground;
    RobotDemo* robotDemo;
    Robot* robot;


    GLfloat m[16];
    float distance;
    float rotationAngle;
    void drawGrid();
    float xRotation;
    float yRotation;
    float sceneDistance;
    map<QString,  GLfloat[16]> matrices;   //matrix for each parent node

    //ODE
    World* w;
public:
    QTimer timer;

    explicit MyGLWidget(QWidget *parent=0);
    static QString jointName;
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    ObjectODE *draw(Link l);
    void adjustPosition();
    void reset();

    float getXRotation() const;
    void setXRotation(float value);
    float getSceneDistance() const;
    void setSceneDistance(float value);

    float getYRotation() const;
    void setYRotation(float value);
    void rotateMe(double r, double p, double y);
    double convertRadToDegrees(double value);



    RobotDemo *getRobot() const;
    void setRobot(ObjectODE *value);

    void moveRightLeg();
    void moveLeftLeg();

public Q_SLOTS:
    void animation();
    void animateAnn(QElapsedTimer annElapsedTimer, ANN *ann, unsigned numOfOutputs);
};

#endif // MYGLWIDGET_H
