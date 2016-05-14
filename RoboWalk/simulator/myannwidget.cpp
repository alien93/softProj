#include "myannwidget.h"

MyAnnWidget::MyAnnWidget(QWidget *parent) : QGLWidget(parent)
{
}

void MyAnnWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(10.0);

}

void MyAnnWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    draw();
}

void MyAnnWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

unsigned MyAnnWidget::findMaxVal(std::vector<unsigned> values)
{
    unsigned maxVal = values[0]+1;
    for(unsigned i=0; i<values.size(); i++)
    {
        if(values[i]+1>maxVal)
        {
            maxVal = values[i]+1;
        }
    }
    return maxVal;
}



//!Draws neural net
//!Window dimensions - width -1 to 1; height -1 to 1
void MyAnnWidget::draw()
{
    unsigned counter = 0;
    //draw neurons
    glBegin(GL_POINTS);
        glColor3f(1.0, 1.0, 1.0);
        for(unsigned i=0; i<annLayers.size(); i++)
        {
            for(unsigned j=0; j<annLayers[i]+1; j++)
            {
                glVertex2f(-1+rowDelta*i+rowDelta/2, -1+j*colDelta+colDelta/2);
                Point2 point = {i, -1+rowDelta*i+rowDelta/2, -1+j*colDelta+colDelta/2};
                nodes.insert(std::pair<unsigned,Point2>(counter++, point));
            }
        }
    glEnd();

    //draw weights
    std::map<unsigned,Point2>::iterator it = nodes.begin();
    std::map<unsigned,Point2>::iterator it2 = nodes.begin();
    for (it=nodes.begin(); it!=nodes.end(); ++it)
    {
        Point2 nodeCoords = it->second;
        unsigned layer = nodeCoords.layerIndex;

        if(layer<annLayers.size())
        {
            for (it2=nodes.begin(); it2!=nodes.end(); ++it2)
            {
                Point2 nodeCoords2 = it2->second;
                unsigned layer2 = nodeCoords2.layerIndex;


                if(layer2-layer==1)
                {
                    glColor3f(1.0, 0.0, 0.0);
                    glLineWidth(0.5);
                    glBegin(GL_LINES);
                        glVertex2f(nodeCoords.x, nodeCoords.y);
                        glVertex2f(nodeCoords2.x, nodeCoords2.y);
                    glEnd();
                }
            }
        }
    }

}

void MyAnnWidget::createNet(const std::vector<unsigned> &layers)
{
    annLayers = layers;
    numCols = annLayers.size();
    numRows = findMaxVal(layers) + 1;       //+ bias
    rowDelta = 2.0/numCols;                 //2.0 - width and hight of glpanel
    colDelta = 2.0/numRows;
    annCreated = true;
    updateGL();
}


