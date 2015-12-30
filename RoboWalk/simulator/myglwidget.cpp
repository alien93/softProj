#include "myglwidget.h"
#include <GL/glut.h>

MyGLWidget::MyGLWidget(QWidget *parent):
    QGLWidget(parent)
{
    distance = -10;
    rotationAngle = 0;
    connect(&timer, SIGNAL(timeout()), this, SLOT(animation()));
    timer.start(16);
}
void MyGLWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

}
void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, -5.0f, 0.0f);
    drawGrid();

    glLoadIdentity();
    glTranslatef(distance, -4.5f, -15.0f);
    glRotatef(rotationAngle, 0, 0, 1);
    sl->drawLegs();


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
    for(float i= -88; i<=88; i++)
    {
        glBegin(GL_LINES);
        glVertex3f(-88.0f, 0.0f, i);
        glVertex3f(88.0f, 0.0f, i);
        glVertex3f(i, 0.0f, -88.0f);
        glVertex3f(i, 0.0f, 88.0f);
        glEnd();
    }
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
