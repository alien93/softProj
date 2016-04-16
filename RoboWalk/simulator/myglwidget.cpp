#include "myglwidget.h"
#include <GL/glut.h>


QString MyGLWidget::jointName = "";


MyGLWidget::MyGLWidget(QWidget *parent):
    QGLWidget(parent)
{
    p = new Physics();

    xRotation=0.0f;
    yRotation = 0.0f;
    sceneDistance=-80.0f;
    gravityAnimation = false;
    limit = 0.1;
   // distance = -10;
   // rotationAngle = 0;
    step = true;
    connect(&timer, SIGNAL(timeout()), this, SLOT(animation()));
    connect(&odeTimer, SIGNAL(timeout()), this, SLOT(gravity()));
}

void MyGLWidget::gravity()
{
    gravityAnimation = true;
    odeTimer.start(20);
    if(odeTime.elapsed() < 2000)
        repaint();
    else
        odeTimer.stop();
}



void MyGLWidget::initializeGL()
{
    p->odeInit();
    glClearColor(0.0f, 0.0f, 0, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

}

void MyGLWidget::paintGL()
{
    //rendering objects
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, -10.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, sceneDistance);
    glRotatef(xRotation, 1.0f, 0.0f, 0.0f);
    glRotatef(yRotation, 0.0f, 1.0f, 0.0f);
    glScalef(30.0f, 30.0f, 30.0f);


    glPushMatrix();
    //glTranslatef(0.0f, -.5f, 0.0f);
    drawGrid();
    glPopMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);


    GLfloat m[16];


    if(parser->getInstance()->getFileParsed())
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

                    this->p->odeCreateObject(lp, links.size());
                }



                //draw child link
                Link lc = linksMap.at(c.getLink());
                //joint transformations
                if(jointName!="" && j.getChild().getLink()==jointName)
                {
                    Axis axis = j.getAxis();
                   /* glTranslated(o.getXyz_x(), o.getXyz_y(), o.getXyz_z());
                    rotateMe(limit*(axis.getX()), limit*(axis.getY()), limit*(axis.getZ()));*/


                }
                else
                {
                   /* glTranslated(o.getXyz_x(), o.getXyz_y(), o.getXyz_z());
                    rotateMe(o.getRpy_r(), o.getRpy_p(), o.getRpy_y());*/
                }







                this->p->odeCreateObject(lc, links.size(), o, j.getAxis());

                //both objects are loaded
                this->p->odeCreateJoint(j, linksMap.at(j.getParent().getLink()), linksMap.at(j.getChild().getLink()), joints.size(), links.size());

            }
            map<QString, Link> newMap = parser->getInstance()->getUsedLinks();
            newMap.clear();
            matrices.clear();
            parser->getInstance()->setUsedLinks(newMap);
        }
        else
            for(vector<Link>::iterator it=links.begin(); it!=links.end(); it++)
            {
                //glPushMatrix();
                Link lp = *it;

                p->odeCreateObject(lp, links.size());

                //glPopMatrix();
            }
    }



        //ode
    if(parser->getInstance()->getFileParsed())
    {
        p->odeLoop();
        if(!gravityAnimation)
            gravity();
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




