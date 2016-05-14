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
    vector<unsigned> neuronsPerLayer;

    unsigned numOfInputs = 6;
    unsigned numOfOutputs = 6;
    unsigned numOfNeurons1hidden = 3;
    neuronsPerLayer.push_back(numOfInputs);
    neuronsPerLayer.push_back(numOfNeurons1hidden);
    neuronsPerLayer.push_back(numOfOutputs);
    ann = new ANN(neuronsPerLayer);
    annSimulation->createNet(neuronsPerLayer);
}

void AnnDemo::trainANN(MyGLWidget *robotSimulation)
{
    animateRobot = false;
    for(int i=0; i<20; i++)
    {
        //preparing training data
        vector<double> inputValues = {0, 0, 0, 0, 0, 0};
        ann->feedForward(inputValues);

        vector<double> resultValues;
        ann->getOutput(resultValues);

        if(round(resultValues[0])==1)
            robotSimulation->getRobot()->rotateRightThigh(30);
        annElapsedTimer.restart();
        robotSimulation->animateAnn(annElapsedTimer);


        vector<double> targetValues = {1, 0, 0, 0, 0, 0};
        ann->backPropagation(targetValues);
    }

    animateRobot = true;
    annCreated = true;
}
