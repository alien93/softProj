#ifndef ANNDEMO_H
#define ANNDEMO_H

#include <QDebug>
#include "ann/ann.h"
#include "objectode.h"
#include <qelapsedtimer.h>
#include "myglwidget.h"
#include "myannwidget.h"


class AnnDemo
{
private:
    ANN* ann;
    bool annCreated;
    bool animateRobot;
    QElapsedTimer annElapsedTimer;
    vector<unsigned> neuronsPerLayer;
    unsigned numOfIterations;
    vector<vector<double>> inputs;
    vector<vector<double>> outputs;
    void printResults(vector<double> results);
public:
    AnnDemo();
    void initRobot(MyGLWidget *robotSimulation);
    void parseTrainingData(QString filename);
    void createANN(MyAnnWidget* annSimulation);
    void trainANN(MyGLWidget* robotSimulation);
    QElapsedTimer getAnnElapsedTimer() const;
    void setAnnElapsedTimer(const QElapsedTimer &value);
};

#endif // ANNDEMO_H
