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
    ann = new ANN(neuronsPerLayer);
    annSimulation->createNet(neuronsPerLayer);
}

void AnnDemo::trainANN(MyGLWidget *robotSimulation)
{
    vector<double> inputValues;
    vector<double> targetValues;
    vector<double> resultValues;


    animateRobot = false;
    for(unsigned j=0; j<numOfIterations; j++)
        for(unsigned i=0; i<inputs.size(); i++)
        {
            //preparing training data
            inputValues = inputs[i];
            ann->feedForward(inputValues);
            qDebug()<<"Input";
            printResults(inputValues);

            ann->getOutput(resultValues);
            qDebug()<<"Output";
            printResults(resultValues);

            targetValues = outputs[i];
            ann->backPropagation(targetValues);
            qDebug()<<"Target value";
            printResults(targetValues);
        }


    annElapsedTimer.restart();
    initRobot(robotSimulation);
    robotSimulation->animateAnn(annElapsedTimer, ann, outputs[0].size());

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
}

void AnnDemo::parseTrainingData(QString filename)
{
    unsigned rowCounter = 0;

    //loading file
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Failed to open file";
        return;
    }
    else
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            QStringList list = line.split(" ");

            if(rowCounter == 0)                     //first row, read topology
            {
                for(unsigned i=0; i<list.size(); i++)
                {
                    neuronsPerLayer.push_back(list[i].toInt());
                }
            }
            else if(rowCounter == 1)                //second row, read number of iterations
            {
                numOfIterations = list[0].toInt();
            }
            else
            {
                if(rowCounter%2 == 0)               //reading inputs
                {
                    vector<double> data;
                    for(unsigned j=0; j<list.size(); j++)
                    {
                        data.push_back(list[j].toDouble());
                    }
                    inputs.push_back(data);
                }
                else
                {
                    vector<double> data;          //reading outputs
                    for(unsigned j=0; j<list.size(); j++)
                    {
                        data.push_back(list[j].toDouble());
                    }
                    outputs.push_back(data);
                }
            }
            rowCounter++;
        }
        file.close();
    }

}
