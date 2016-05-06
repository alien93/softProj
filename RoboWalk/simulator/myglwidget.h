#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H
<<<<<<< HEAD
=======


>>>>>>> origin

#include <QGLWidget>
#include <QTimer>
#include "simplelegs.h"
#include "drawcylinder.h"
#include "drawsphere.h"
#include "drawbox.h"
#include <vector>
#include "model/visual.h"
#include <array>
#include <ode/ode.h>
#include "physics.h"

using namespace std;

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
private:
    URDFparser *parser;
    bool step;
    bool gravityAnimation;
    SimpleLegs *sl;
    DrawCylinder *cylinder;
    DrawBox *box;
    DrawSphere *sphere;
    URDFparser *parser;
    GLfloat m[16];
    double limit;
    float distance;
    float rotationAngle;
    void drawGrid();
    void drawRobot();
    float xRotation;
    float yRotation;
    float sceneDistance;
    map<QString,  GLfloat[16]> matrices;   //matrix for each parent node

<<<<<<< HEAD
    //ODE
    World* w;
=======
    QTimer odeTimer;

>>>>>>> origin
public:
    QTimer timer;
    QTime odeTime;

    Physics* p;


    explicit MyGLWidget(QWidget *parent=0);
    static QString jointName;
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void draw(Link l);
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


public Q_SLOTS:
    void animation();
    void gravity();
};

#endif // MYGLWIDGET_H
