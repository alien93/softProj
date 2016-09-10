#include "myglwidget.h"
#include <GL/glut.h>


QString MyGLWidget::jointName = "";


MyGLWidget::MyGLWidget(QWidget *parent):
    QGLWidget(parent)
{
    xRotation=0.0f;
    yRotation = -90.0f;
    sceneDistance=-50.0f;
    limit = 0.1;
    step = true;
    connect(&timer, SIGNAL(timeout()), this, SLOT(animation()));
}

void MyGLWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0, 1.0f);
    glEnable(GL_DEPTH_TEST);
    w = new World(-0.05);                         //initialise ode world
    ground = new DrawBox(w, false, 20, 0.01, 20, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0);  //setup ground
    Point3 position = {0, 0, 0};
    ground->setPosition(position);
    Point3 initPosition = {0, 0.38, 0};     //initial torso position
    robot = new RobotDemo(w, initPosition.x, initPosition.y, initPosition.z, (dReal)0.1);
    initPositions.push_back(robot->getR_upperLeg()->getPosition());
    initPositions.push_back(robot->getL_upperLeg()->getPosition());
    initPositions.push_back(robot->getR_lowerLeg()->getPosition());
    initPositions.push_back(robot->getL_lowerLeg()->getPosition());
    initPositions.push_back(robot->getR_foot()->getPosition());
    initPositions.push_back(robot->getL_foot()->getPosition());

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
    glTranslatef(0.0f, -.04f, 0.0f);
    drawGrid();
    glPopMatrix();
    robot->draw();
    glPopMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    w->loop();


    /* if(parser->getInstance()->getFileParsed())
    {
        drawRobot();    //robot from urdf
    }*/
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

//!Draws a robot
void MyGLWidget::drawRobot()
{
    map<QString, MyLink> linksMap = parser->getInstance()->rm.getLinks();
    vector<MyLink> links = parser->getInstance()->rm.getLinksVector();
    map<QString, Joint> jointsMap = parser->getInstance()->rm.getJoints();
    // vector<Joint> joints = parser->getInstance()->rm.getJointsVector();
    vector<Joint> joints = parser->getInstance()->rm.sortJoints(jointsMap);

    if(joints.size()!=0)
    {
        for(vector<Joint>::iterator it=joints.begin(); it!=joints.end(); it++)
        {
            //Joint j = it->second;
            Joint j = *it;
            Parent p = j.getParent();   //parent
            Child c = j.getChild();     //child
            Origin o = j.getOrigin();   //position of the child link relative to parent link
            //draw parent link
            //  glPushMatrix();
            MyLink lp = linksMap.at(p.getLink());
            map<QString, MyLink> usedLinks = parser->getInstance()->getUsedLinks();
            map<QString, MyLink>::iterator iter = usedLinks.find(lp.getName());
            if(usedLinks.count(lp.getName()))
            {
                //the link already exists
                glLoadMatrixf(matrices.at(lp.getName()));
                elem1 = draw(lp);
            }
            else
            {
                glGetFloatv (GL_MODELVIEW_MATRIX, m);
                for(int i=0; i<16; i++)
                {
                    matrices[lp.getName()][i] = m[i];
                }
                usedLinks[lp.getName()] = lp;
                parser->getInstance()->setUsedLinks(usedLinks);
                elem1 = draw(lp);
            }
            //joint transformations
            if(jointName!="" && j.getChild().getLink()==jointName)
            {
                Axis axis = j.getAxis();
                glTranslated(o.getXyz_x(), o.getXyz_y(), o.getXyz_z());
                rotateMe(limit*(axis.getX()), limit*(axis.getY()), limit*(axis.getZ()));

            }
            else
            {
                glTranslated(o.getXyz_x(), o.getXyz_y(), o.getXyz_z());
                rotateMe(o.getRpy_r(), o.getRpy_p(), o.getRpy_y());
            }


            //draw child link
            MyLink lc = linksMap.at(c.getLink());
            elem2 = draw(lc);


            //create joints
            if(elem1 != NULL && elem2 != NULL)
            {
                dJointID joint = dJointCreateHinge(w->getWorldID(), 0);
                dJointAttach(joint, elem1->getBodyID(), elem2->getBodyID());
                Point3 jointPoint = {(dReal)j.getOrigin().getXyz_x(), (dReal)j.getOrigin().getXyz_y(), (dReal)j.getOrigin().getXyz_z()};
                dJointSetHingeAnchor(joint, jointPoint.x, jointPoint.y, jointPoint.z);
                dJointSetHingeAxis(joint, 1, 0, 0);
                dJointSetHingeParam(joint, dParamLoStop, j.getLimit().getLower());
                dJointSetHingeParam(joint, dParamHiStop, j.getLimit().getUpper());
            }
        }
        map<QString, MyLink> newMap = parser->getInstance()->getUsedLinks();
        newMap.clear();
        matrices.clear();
        parser->getInstance()->setUsedLinks(newMap);
    }
    else
        //single link, no joints
        for(vector<MyLink>::iterator it=links.begin(); it!=links.end(); it++)
        {
            glPushMatrix();
            MyLink lp = *it;
            draw(lp);
            glPopMatrix();
        }
}


//!Draws a link
ObjectODE* MyGLWidget::draw(MyLink l)
{
    vector<Visual> visuals = l.getVisual();
    if(visuals.size()>0)
    {
        for(vector<Visual>::iterator it=visuals.begin(); it!=visuals.end(); it++)
        {
            Origin o = it->getOrigin();
            Geometry g = it->getGeometry();
            Material m = it->getMaterial();

            if(g.getObject().getName() == "cylinder")
            {
                double length = g.getObject().getLength();
                double radius = g.getObject().getRadius();
                double r = o.getRpy_r();
                double p = o.getRpy_p();
                double yy = o.getRpy_y();
                double x = o.getXyz_x();
                double y = o.getXyz_y();
                double z = o.getXyz_z();
                double red = m.getColor().getRed();
                double green = m.getColor().getGreen();
                double blue = m.getColor().getBlue();
                double alpha = m.getColor().getAlpha();

                cylinder = new DrawCylinder(w, true, length, radius,
                                            r, p, yy,
                                            x, y, z,
                                            red, green, blue, alpha);
                cylinder->draw();
                return cylinder;
            }
            else if(g.getObject().getName() == "box")
            {
                double width = g.getObject().getWidth();
                double height = g.getObject().getHeight();
                double depth = g.getObject().getDepth();
                double r = o.getRpy_r();
                double p = o.getRpy_p();
                double yy = o.getRpy_y();
                double x = o.getXyz_x();
                double y = o.getXyz_y();
                double z = o.getXyz_z();
                double red = m.getColor().getRed();
                double green = m.getColor().getGreen();
                double blue = m.getColor().getBlue();
                double alpha = m.getColor().getAlpha();

                box = new DrawBox(w, true, width, height, depth,
                                  r, p, yy,
                                  x, y, z,
                                  red, green, blue, alpha);
                box->draw();
                return box;
            }
            else if(g.getObject().getName() == "sphere")
            {
                double radius = g.getObject().getSphereRadius();
                double r = o.getRpy_r();
                double p = o.getRpy_p();
                double yy = o.getRpy_y();
                double x = o.getXyz_x();
                double y = o.getXyz_y();
                double z = o.getXyz_z();
                double red = m.getColor().getRed();
                double green = m.getColor().getGreen();
                double blue = m.getColor().getBlue();
                double alpha = m.getColor().getAlpha();

                sphere = new DrawSphere(w, true,  radius,
                                        r, p, yy,
                                        x, y, z,
                                        red, green, blue, alpha);
                sphere->draw();
                return sphere;
            }
        }
    }
    return NULL;
}

//!Draws a ground
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
        if(limit<lowerLimit)
            limit = lowerLimit;
        else if(limit<=upperLimit && limit>=lowerLimit)
            limit+=0.01;
        else if(limit>upperLimit)
        {
            limit = upperLimit;
            step = false;
        }
    }
    else
    {
        if(limit>upperLimit)
            limit = upperLimit;
        else if(limit<=upperLimit && limit>=lowerLimit)
            limit-=0.01;
        else if(limit<lowerLimit)
        {
            limit = lowerLimit;
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

        if(round(robot->getPosition().y*10)/10 <= 0.25)      //robot's on the ground, reinitialise
            robot->setPosition({0, 0.38, 0});

        inputs.push_back(round(dJointGetHingeAngle(robot->getR_hip()) * 10)/10);
        inputs.push_back(round(dJointGetHingeAngle(robot->getL_hip()) * 10)/10);
        inputs.push_back(round(dJointGetHingeAngle(robot->getR_knee()) * 10)/10);
        inputs.push_back(round(dJointGetHingeAngle(robot->getL_knee()) * 10)/10);
        inputs.push_back(round(dJointGetHingeAngle(robot->getR_ankle()) * 10)/10);
        inputs.push_back(round(dJointGetHingeAngle(robot->getL_ankle()) * 10)/10);

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
                dJointAddHingeTorque(robot->getR_hip(), 50);
            if(round(result[0]) == -1)
                dJointAddHingeTorque(robot->getR_hip(), -50);
            if(round(result[1]) == 1)
                dJointAddHingeTorque(robot->getL_hip(), 50);
            if(round(result[1]) == -1)
                dJointAddHingeTorque(robot->getL_hip(), -50);
            if(round(result[2]) == 1)
                dJointAddHingeTorque(robot->getR_knee(), 20);
            if(round(result[2]) == -1)
                dJointAddHingeTorque(robot->getR_knee(), -20);
            if(round(result[3]) == 1)
                dJointAddHingeTorque(robot->getL_knee(), 20);
            if(round(result[3]) == -1)
                dJointAddHingeTorque(robot->getL_knee(), -20);
            if(round(result[4]) == 1)
                dJointAddHingeTorque(robot->getR_ankle(), 20);
            if(round(result[4]) == -1)
                dJointAddHingeTorque(robot->getR_ankle(), -20);
            if(round(result[5]) == 1)
                dJointAddHingeTorque(robot->getL_ankle(), 20);
            if(round(result[5]) == -1)
                dJointAddHingeTorque(robot->getL_ankle(), -20);
        }
        repaint();
    }
}

//returns fitness
double MyGLWidget::animateAnn(Network *net, int thresh, vector<float> inputs, QElapsedTimer annElapsedTimer)
{
    vector<double> result;
    vector<NNode*>::iterator out_iter;
    net->load_sensors(inputs);
    double points = 0;

    while(!annElapsedTimer.hasExpired(5000))
    {
        inputs.clear();
        result.clear();

        inputs.push_back(round(dJointGetHingeAngle(robot->getR_hip()) * 10)/10);
        inputs.push_back(round(dJointGetHingeAngle(robot->getL_hip()) * 10)/10);
        inputs.push_back(round(dJointGetHingeAngle(robot->getR_knee()) * 10)/10);
        inputs.push_back(round(dJointGetHingeAngle(robot->getL_knee()) * 10)/10);
        inputs.push_back(round(dJointGetHingeAngle(robot->getR_ankle()) * 10)/10);
        inputs.push_back(round(dJointGetHingeAngle(robot->getL_ankle()) * 10)/10);
        net->load_sensors(inputs);


        if(!(net->activate())) return 1;

        out_iter = net->outputs.begin();
        for(int i=0; i<6; i++)
        {
            result.push_back((*out_iter)->activation);
            ++out_iter;
        }


        if(round(result[0]) == 1)
            dJointAddHingeTorque(robot->getR_hip(), 50);
        if(round(result[0]) == -1)
            dJointAddHingeTorque(robot->getR_hip(), -50);
        if(round(result[1]) == 1)
            dJointAddHingeTorque(robot->getL_hip(), 50);
        if(round(result[1]) == -1)
            dJointAddHingeTorque(robot->getL_hip(), -50);
        if(round(result[2]) == 1)
            dJointAddHingeTorque(robot->getR_knee(), 20);
        if(round(result[2]) == -1)
            dJointAddHingeTorque(robot->getR_knee(), -20);
        if(round(result[3]) == 1)
            dJointAddHingeTorque(robot->getL_knee(), 20);
        if(round(result[3]) == -1)
            dJointAddHingeTorque(robot->getL_knee(), -20);
        if(round(result[4]) == 1)
            dJointAddHingeTorque(robot->getR_ankle(), 20);
        if(round(result[4]) == -1)
            dJointAddHingeTorque(robot->getR_ankle(), -20);
        if(round(result[5]) == 1)
            dJointAddHingeTorque(robot->getL_ankle(), 20);
        if(round(result[5]) == -1)
            dJointAddHingeTorque(robot->getL_ankle(), -20);

        points += rewards();

        if(round(robot->getPosition().y*10)/10 <= 0.1 ||   //robot's on the ground
           round(robot->getPosition().y*10)/10 >= 0.5)      //robot's jumping
        {
            robot->setPosition({0, 0.38, 0});
            return robot->getPosition().z;
        }

        repaint();
    }

    return robot->getPosition().z + points/1000;
}


double MyGLWidget::rewards()
{
    double reward = 0;

    if(round(robot->getL_foot()->getPosition().y*10)/10 != round(robot->getR_foot()->getPosition().y*10)/10) //feet are not on the same level
        reward += 0.1;

    if(round(dJointGetHingeAngle(robot->getR_knee()) * 10)/10 != 0 || round(dJointGetHingeAngle(robot->getL_knee()) * 10)/10 != 0) //robot's using knees
        reward += 0.3;

    if(round(robot->getL_foot()->getPosition().y*10)/10 > 0 || round(robot->getR_foot()->getPosition().y*10)/10 > 0) //using feet
        reward += 0.5;

    return reward;
}

void MyGLWidget::moveRightLeg()
{

    robot->getR_lowerLeg()->setPosition({robot->getR_lowerLeg()->getPosition().x, robot->getR_lowerLeg()->getPosition().y, robot->getR_lowerLeg()->getPosition().z + 0.09});
    robot->getR_foot()->setPosition({robot->getR_foot()->getPosition().x, robot->getR_foot()->getPosition().y, robot->getR_foot()->getPosition().z + 0.1});
}

void MyGLWidget::moveLeftLeg()
{
    robot->getL_lowerLeg()->setPosition({robot->getL_lowerLeg()->getPosition().x, robot->getL_lowerLeg()->getPosition().y, robot->getL_lowerLeg()->getPosition().z + 0.09});
    robot->getL_foot()->setPosition({robot->getL_foot()->getPosition().x, robot->getL_foot()->getPosition().y, robot->getL_foot()->getPosition().z + 0.1});
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
    return robot;
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



