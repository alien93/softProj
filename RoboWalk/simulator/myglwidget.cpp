#include "myglwidget.h"
#include <GL/glut.h>


QString MyGLWidget::jointName = "";


MyGLWidget::MyGLWidget(QWidget *parent):
    QGLWidget(parent)
{
    xRotation=0.0f;
    yRotation = -90.0f;
    sceneDistance=-50.0f;
    step = true;
    robotLoaded = false;
    connect(&timer, SIGNAL(timeout()), this, SLOT(animation()));
}

void MyGLWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0, 1.0f);
    glEnable(GL_DEPTH_TEST);
    w = new World(-9.81);                         //initialise ode world
    //ground = new DrawBox(w, false, 20, 0.1, 20, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0);  //setup ground
    //Point3 position = {0, 0, 0};
    //ground->setPosition(position);
    //Point3 initPosition = {0, 0.5, 0};     //initial torso position
    //robotDemo = new RobotDemo(w, initPosition.x, initPosition.y, initPosition.z, (dReal)0.1);
    //robot = new Robot(w, initPosition.x, initPosition.y, initPosition.z);
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, -10.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, sceneDistance);
    glRotatef(xRotation, 1.0f, 0.0f, 0.0f);
    glRotatef(yRotation, 0.0f, 1.0f, 0.0f);
    glScalef(30.0f, 30.0f, 30.0f);

    glPushMatrix();
    //glTranslatef(0.0f, -.04f, 0.0f);
    drawGrid();
    glPopMatrix();
    //robotDemo->draw();    //demo robot
    glPopMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);


    if(parser->getInstance()->getFileParsed())
    {
        if(!robotLoaded)
        {
            Point3 initPosition = {0, 0, 0};     //initial torso position
            robot = new Robot(w, initPosition.x, initPosition.y, initPosition.z);
            robotLoaded = true;

        }
        robot->draw(); //robot from URDF
        w->loop();
    }
}

void MyGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 1.0, 150.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}


//!Draws ground
void MyGLWidget::drawGrid()
{
    glColor3ub(0,255,255);
    for(float i= -88; i<=88; i+=0.1)
    {
        glBegin(GL_LINES);
        glVertex3f(-88.0f, 0.0f, i);
        glVertex3f(88.0f, 0.0f, i);
        glVertex3f(i, 0.0f, -88.0f);
        glVertex3f(i, 0.0f, 88.0f);
        glEnd();
    }
    //ground->draw();
}

//!Animating joint movements
void MyGLWidget::animation()
{
    URDFparser *parser;
    map<QString, Joint> jointsMap = parser->getInstance()->rm.getJoints();
    vector<Joint> joints = parser->getInstance()->rm.sortJoints(jointsMap);
    double lowerLimit, upperLimit;

    if(joints.size()!=0)
    {
        for(vector<Joint>::iterator it=joints.begin(); it!=joints.end(); it++)
        {
            Joint j = *it;
            if(jointName!="" && j.getChild().getLink()==jointName)
            {

                lowerLimit = j.getLimit().getLower();
                upperLimit = j.getLimit().getUpper();
                break;

            }
        }
    }

    if(lowerLimit>upperLimit)
    {
        double temp = upperLimit;
        upperLimit = lowerLimit;
        lowerLimit = temp;
    }

    if(step)
    {
        if(robot->getLimit()<lowerLimit)
            robot->setLimit(lowerLimit);
        else if(robot->getLimit()<=upperLimit && robot->getLimit()>=lowerLimit)
            robot->setLimit(robot->getLimit()+0.01);
        else if(robot->getLimit()>upperLimit)
        {
            robot->setLimit(upperLimit);
            step = false;
        }
    }
    else
    {
        if(robot->getLimit()>upperLimit)
            robot->setLimit(upperLimit);
        else if(robot->getLimit()<=upperLimit && robot->getLimit()>=lowerLimit)
            robot->setLimit(robot->getLimit()-0.01);
        else if(robot->getLimit()<lowerLimit)
        {
            robot->setLimit(lowerLimit);
            step = true;
        }
    }
    update();
}

//!Animating the training process of ANN
void MyGLWidget::animateAnn(QElapsedTimer annElapsedTimer, ANN* ann, unsigned numOfOutputs)
{
    vector<double> inputs;
    vector<double> result;


    while(!annElapsedTimer.hasExpired(30000))
    {
        inputs.clear();
        result.clear();

        if(round(robotDemo->getPosition().y*10)/10 <= 0.25)      //robot's on the ground, reinitialise
            robotDemo->setPosition({0, 0.38, 0});

        inputs.push_back(round(dJointGetHingeAngle(robotDemo->getR_hip()) * 10)/10);
        inputs.push_back(round(dJointGetHingeAngle(robotDemo->getL_hip()) * 10)/10);
        inputs.push_back(round(dJointGetHingeAngle(robotDemo->getR_knee()) * 10)/10);
        inputs.push_back(round(dJointGetHingeAngle(robotDemo->getL_knee()) * 10)/10);
        inputs.push_back(round(dJointGetHingeAngle(robotDemo->getR_ankle()) * 10)/10);
        inputs.push_back(round(dJointGetHingeAngle(robotDemo->getL_ankle()) * 10)/10);

        ann->feedForward(inputs);

        ann->getOutput(result);


        if(numOfOutputs == 2)
        {
            if(annElapsedTimer.elapsed()%1000 == 0)
            {
                if(round(result[0])==1)
                {
                    moveRightLeg();

                }
                else if(round(result[1])==1)
                {
                    moveLeftLeg();

                }
            }
        }
        else if(numOfOutputs == 6)
        {
                if(round(result[0]) == 1)
                    dJointAddHingeTorque(robotDemo->getR_hip(), 50);
                if(round(result[0]) == -1)
                    dJointAddHingeTorque(robotDemo->getR_hip(), -50);
                if(round(result[1]) == 1)
                    dJointAddHingeTorque(robotDemo->getL_hip(), 50);
                if(round(result[1]) == -1)
                    dJointAddHingeTorque(robotDemo->getL_hip(), -50);
                if(round(result[2]) == 1)
                    dJointAddHingeTorque(robotDemo->getR_knee(), 20);
                if(round(result[2]) == -1)
                    dJointAddHingeTorque(robotDemo->getR_knee(), -20);
                if(round(result[3]) == 1)
                    dJointAddHingeTorque(robotDemo->getL_knee(), 20);
                if(round(result[3]) == -1)
                    dJointAddHingeTorque(robotDemo->getL_knee(), -20);
                if(round(result[4]) == 1)
                    dJointAddHingeTorque(robotDemo->getR_ankle(), 20);
                if(round(result[4]) == -1)
                    dJointAddHingeTorque(robotDemo->getR_ankle(), -20);
                if(round(result[5]) == 1)
                    dJointAddHingeTorque(robotDemo->getL_ankle(), 20);
                if(round(result[5]) == -1)
                    dJointAddHingeTorque(robotDemo->getL_ankle(), -20);
        }
        repaint();
    }
}

void MyGLWidget::moveRightLeg()
{

    robotDemo->getR_lowerLeg()->setPosition({robotDemo->getR_lowerLeg()->getPosition().x, robotDemo->getR_lowerLeg()->getPosition().y, robotDemo->getR_lowerLeg()->getPosition().z + 0.09});
    robotDemo->getR_foot()->setPosition({robotDemo->getR_foot()->getPosition().x, robotDemo->getR_foot()->getPosition().y, robotDemo->getR_foot()->getPosition().z + 0.1});
}

void MyGLWidget::moveLeftLeg()
{
    robotDemo->getL_lowerLeg()->setPosition({robotDemo->getL_lowerLeg()->getPosition().x, robotDemo->getL_lowerLeg()->getPosition().y, robotDemo->getL_lowerLeg()->getPosition().z + 0.09});
    robotDemo->getL_foot()->setPosition({robotDemo->getL_foot()->getPosition().x, robotDemo->getL_foot()->getPosition().y, robotDemo->getL_foot()->getPosition().z + 0.1});
}

void MyGLWidget::reset()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glFlush();
}

float MyGLWidget::getYRotation() const
{
    return yRotation;
}

void MyGLWidget::setYRotation(float value)
{
    yRotation = value;
}

float MyGLWidget::getSceneDistance() const
{
    return sceneDistance;
}

void MyGLWidget::setSceneDistance(float value)
{
    sceneDistance = value;
}

float MyGLWidget::getXRotation() const
{
    return xRotation;
}

void MyGLWidget::setXRotation(float value)
{
    xRotation = value;
}

RobotDemo *MyGLWidget::getRobot() const
{
    return robotDemo;
}


void MyGLWidget::rotateMe(double r, double p, double y)
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

double MyGLWidget::convertRadToDegrees(double value)
{
    double retVal;
    retVal = value * 180 / M_PI;
    return retVal;
}



