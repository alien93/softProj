#include "myglwidget.h"
#include <GL/glut.h>


MyGLWidget::MyGLWidget(QWidget *parent):
    QGLWidget(parent)
{
    xRotation=0.0f;
    yRotation = 0.0f;
    sceneDistance=-50.0f;
   // distance = -10;
   // rotationAngle = 0;
   // connect(&timer, SIGNAL(timeout()), this, SLOT(animation()));
   // timer.start(16);
}
void MyGLWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

}
void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, -5.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, sceneDistance);
    glRotatef(xRotation, 1.0f, 0.0f, 0.0f);
    glRotatef(yRotation, 0.0f, 1.0f, 0.0f);
    glScalef(30.0f, 30.0f, 30.0f);

    glPushMatrix();
    glTranslatef(0.0f, -.5f, 0.0f);
    drawGrid();
    glPopMatrix();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
   // glTranslatef(0.0f, -15, .0f);
    //glTranslatef(distance, -4.5f, -15.0f);
    //glRotatef(rotationAngle, 0, 0, 1);
    //sl->drawLegs();
    URDFparser *parser;
    if(parser->getInstance()->getFileParsed())
    {
        map<QString, Link> links = parser->getInstance()->rm.getLinks();
        map<QString, Joint> joints = parser->getInstance()->rm.getJoints();
        if(joints.size()!=0)
            for(map<QString, Joint>::iterator it=joints.begin(); it!=joints.end(); it++)
            {
                Joint j = it->second;
                Parent p = j.getParent();   //parent
                Child c = j.getChild();     //child
                Origin o = j.getOrigin();   //position of the child link relative to parent link
                //draw parent link
                glPushMatrix();
                Link lp = links.at(p.getLink());
                drawCylinder(lp, 0.0, 0.0, 0.0);
                 //draw child link
                Link lc = links.at(c.getLink());
                drawCylinder(lc, o.getXyz_x(), o.getXyz_z(), o.getXyz_y());
                glPopMatrix();
            }
        else
            for(map<QString, Link>::iterator it=links.begin(); it!=links.end(); it++)
            {
                Link j = it->second;

                //draw parent link
                glPushMatrix();
                Link lp = it->second;
                drawCylinder(lp, 0.0, 0.0, 0.0);
                glPopMatrix();
            }
    }
    glFlush();
}


void MyGLWidget::drawCylinder(Link l, double xc, double yc, double zc)
{
    vector<Visual> visuals = l.getVisual();
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

            cylinder = new DrawCylinder(length, radius,
                                        r, p, yy,
                                        x, y, z,
                                        red, green, blue, alpha);
            cylinder->drawCylinder(xc, yc, zc);
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

            box = new DrawBox(width, height, depth,
                              r, p, yy,
                              x, y, z,
                              red, green, blue, alpha);
            box->drawBox(xc, yc, zc);
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

            sphere = new DrawSphere(radius,
                                    r, p, yy,
                                    x, y, z,
                                    red, green, blue, alpha);
            sphere->drawSphere(xc, yc, zc);
        }
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
    if(rotationAngle<360)
        rotationAngle+=30;
    else
        rotationAngle = 0;

    if(distance < 10)
        distance+=0.1;
    else
        distance = -10;
    update();
}

void MyGLWidget::reset()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glFlush();
}
