#include "myglwidget.h"
#include <GL/glut.h>


QString MyGLWidget::jointName = "";


MyGLWidget::MyGLWidget(QWidget *parent):
    QGLWidget(parent)
{
    xRotation=0.0f;
    yRotation = 0.0f;
    sceneDistance=-80.0f;
    limit = 0.1;
    // distance = -10;
    // rotationAngle = 0;
    step = true;
    connect(&timer, SIGNAL(timeout()), this, SLOT(animation()));
    // timer.start(16);
}

void MyGLWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    w = new World(-1.0);    //initialise ode

    //setup ground
    ground = new DrawBox(w, false, 20, 0.01, 20, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0);
    Point3 position = {0, 0, 0};
    ground->setPosition(position);

    Point3 initPosition = {0, 0.4, 0};
    robot = new RobotDemo(w, initPosition.x, initPosition.y, initPosition.z, (dReal)0.1);


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

    // world->stepSimulation();
    glPushMatrix();
    //glTranslatef(0.0f, -.5f, 0.0f);
    drawGrid();     //ground
    ground->draw();
    robot->draw();
    glPopMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    if(parser->getInstance()->getFileParsed())
    {
        drawRobot();    //robot
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


void MyGLWidget::drawRobot()
{
    map<QString, Link> linksMap = parser->getInstance()->rm.getLinks();
    vector<Link> links = parser->getInstance()->rm.getLinksVector();
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
            Link lp = linksMap.at(p.getLink());
            map<QString, Link> usedLinks = parser->getInstance()->getUsedLinks();
            map<QString, Link>::iterator iter = usedLinks.find(lp.getName());
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
            qDebug()<<jointName;
            qDebug()<<j.getParent().getLink();
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
            Link lc = linksMap.at(c.getLink());
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
        map<QString, Link> newMap = parser->getInstance()->getUsedLinks();
        newMap.clear();
        matrices.clear();
        parser->getInstance()->setUsedLinks(newMap);
    }
    else
        //single link, no joints
        for(vector<Link>::iterator it=links.begin(); it!=links.end(); it++)
        {
            glPushMatrix();
            Link lp = *it;
            draw(lp);
            glPopMatrix();
        }
}


//draw a link
ObjectODE* MyGLWidget::draw(Link l)
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
    /* ObjectODE* ground = new DrawBox(w, false, 160.0,1.0,160.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0);
    Point3 position = {0, -1, 0};
    ground->setPosition(position);
    ground->draw();*/
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
    /*   if(rotationAngle<360)
        rotationAngle+=30;
    else
        rotationAngle = 0;

    if(distance < 10)
        distance+=0.1;
    else
        distance = -10;*/
    w->loop();

    if(lowerLimit>upperLimit)
    {
        double temp = upperLimit;
        upperLimit = lowerLimit;
        lowerLimit = temp;
    }
    qDebug()<<"hello from animation";
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

void MyGLWidget::reset()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glFlush();
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




