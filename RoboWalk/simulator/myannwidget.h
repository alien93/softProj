#ifndef MYANNWIDGET_H
#define MYANNWIDGET_H

#include <QWidget>
#include <QGLWidget>
#include <vector>
#include <map>
#include <QDebug>
#include <GL/glu.h>

typedef struct Point2
{
    unsigned layerIndex;
    double x;
    double y;
}Point2;

class MyAnnWidget : public QGLWidget
{
    Q_OBJECT
private:
    bool annCreated;
    std::vector<unsigned> annLayers;
    std::map<unsigned, Point2> nodes;
    unsigned numCols;
    unsigned numRows;
    double rowDelta;    //for panel net
    double colDelta;

    unsigned findMaxVal(std::vector<unsigned> values);
public:
    explicit MyAnnWidget(QWidget *parent = 0);
    void draw();
    void createNet(const std::vector<unsigned> &layers);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

signals:

public slots:
};



#endif // MYANNWIDGET_H
