#include "anndemo.h"


AnnDemo::AnnDemo()
{

}

//!///////////////////////////////////////////////////////////
//!//for ANN with 2 hidden layers the neuronsPerLayer vector
//!should look something like this {2, 3, 3, 1}
//!2-number of neurons, input value
//!1-number of neurons, output value
//!3-number of neurons per hidden layer
//!////////////////////////////////////////////////////////////
void AnnDemo::createANN(MyAnnWidget* annSimulation)
{
    vector<unsigned> neuronsPerLayer = {6, 3, 6};
    ann = new ANN(neuronsPerLayer);
    annSimulation->createNet(neuronsPerLayer);
}

void AnnDemo::trainANN(MyGLWidget *robotSimulation)
{
    vector<double> inputValues;
    vector<double> targetValues;
    vector<double> resultValues;

    vector<vector<double>> inputs;
    vector<vector<double>> outputs;
    inputs.push_back({0, 0, 0, 0, 0, 0});       //starting position
    outputs.push_back({0, 0, 1, 0, 0, 0});      //rotate right foot CW

    animateRobot = false;
    for(int j=0; j<100; j++)
    for(int i=0; i<inputs.size(); i++)
    {
        //preparing training data
        inputValues = inputs[i];
        ann->feedForward(inputValues);

        resultValues;
        ann->getOutput(resultValues);
        printResults(resultValues);

        annElapsedTimer.restart();
        initRobot(robotSimulation);
        robotSimulation->animateAnn(annElapsedTimer, resultValues);

        targetValues = outputs[i];
        ann->backPropagation(targetValues);


    }


    animateRobot = true;
    annCreated = true;
}


void AnnDemo::printResults(vector<double> results)
{
    qDebug()<<"-----------------------------";
    for(int i=0; i<results.size(); i++)
    {
        qDebug()<<results[i];
    }
    qDebug()<<"-----------------------------";

}

void AnnDemo::initRobot(MyGLWidget *robotSimulation)
{
     robotSimulation->getRobot()->setPosition({0, 0.38, 0});

    /* robotSimulation->getRobot()->setPosition({0, 0.38, 0});
     robotSimulation->getRobot()->getR_upperLeg()->setPosition(initPositions[0]);
     robotSimulation->getRobot()->getL_upperLeg()->setPosition(initPositions[1]);
     robotSimulation->getRobot()->getR_lowerLeg()->setPosition(initPositions[2]);
     robotSimulation->getRobot()->getL_lowerLeg()->setPosition(initPositions[3]);
     robotSimulation->getRobot()->getR_foot()->setPosition(initPositions[4]);
     robotSimulation->getRobot()->getL_foot()->setPosition(initPositions[5]);*/
}
