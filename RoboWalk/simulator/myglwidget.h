#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include "simplelegs.h"
#include "drawcylinder.h"
#include "drawsphere.h"
#include "drawbox.h"
#include <vector>
#include "model/visual.h"

using namespace std;


class MyGLWidget : public QGLWidget
{
    Q_OBJECT
private:
    QTimer timer;
    SimpleLegs *sl;
    DrawCylinder *cylinder;
    DrawBox *box;
    DrawSphere *sphere;
    float distance;
    float rotationAngle;
    void drawGrid();
    float xRotation;
    float yRotation;
    float sceneDistance;
public:
    explicit MyGLWidget(QWidget *parent=0);
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

public Q_SLOTS:
    void animation();
};

#endif // MYGLWIDGET_H
