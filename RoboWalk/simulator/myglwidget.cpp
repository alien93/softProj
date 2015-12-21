#include "myglwidget.h"
#include <GL/glut.h>

MyGLWidget::MyGLWidget(QWidget *parent):
    QGLWidget(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(animation()));
    timer.start(16);
}
void MyGLWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

}
void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawGrid();
}
void MyGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 1.0, 150.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0.5,3,0,0,0,0,3,0);

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

}
