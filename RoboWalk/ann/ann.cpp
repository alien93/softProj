#include "ann.h"


ANN::ANN(const vector<unsigned> &neuronsPerLayer)
{
    unsigned numOfLayers = neuronsPerLayer.size();  //{2,3,3,1}

    //creating layers
    for(int i=0; i<numOfLayers; i++)
    {
        vector<Neuron> neurons;
        layers.push_back(neurons);

        //creating neurons for the newly created layer
        for(int j=0; j<=neuronsPerLayer[i]; j++)
        {
            layers.back().push_back(Neuron());
            qDebug()<<"Neuron: ";
            qDebug()<<i;
            qDebug()<<j;
        }
    }
}

void ANN::feedForward(const vector<double> &inputValues)
{

}

void ANN::backPropagation(const vector<double> &targetValues)
{

}

void ANN::getOutput(vector<double> &outputValues) const
{

}
