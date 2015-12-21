#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <QTimer>

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
private:
    QTimer timer;
    void drawGrid();
public:
    explicit MyGLWidget(QWidget *parent=0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
public Q_SLOTS:
    void animation();
};

#endif // MYGLWIDGET_H
