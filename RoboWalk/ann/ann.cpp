#include "ann.h"


ANN::ANN(const vector<unsigned> &neuronsPerLayer)
{
    unsigned numOfLayers = neuronsPerLayer.size();  //{2,3,3,1}

    //creating layers
    for(unsigned i=0; i<numOfLayers; i++)
    {
        vector<Neuron> neurons;
        layers.push_back(neurons);
        unsigned numNrNextLayer = i==neuronsPerLayer.size() - 1 ? 0 : neuronsPerLayer[i + 1];
        //creating neurons for the newly created layer
        //number of requested neurons + bias
        for(unsigned j=0; j<=neuronsPerLayer[i]; j++)
        {
            layers.back().push_back(Neuron(numNrNextLayer, j));
            qDebug()<<"Neuron: ";
            qDebug()<<i;
            qDebug()<<j;
        }
    }
}

void ANN::feedForward(const vector<double> &inputValues)
{
    assert(inputValues.size() == layers[0].size() - 1 &&
           "Number of input values is different than number"
           "of nodes in the input layer. Terminating.");

    //put input values in input neurons
    for(unsigned i=0; i<inputValues.size(); i++)
    {
        layers[0][i].setOutputValue(inputValues.at(i));
    }

    //forward propagation
    for (unsigned i = 1; i < layers.size(); i++)
    {
        vector<Neuron> &previousLayer = layers[i - 1];
        for(unsigned j = 0; j < layers[i].size() - 1; j++)
        {
            layers[i][j].feedForward(previousLayer);
        }
    }

}

void ANN::backPropagation(const vector<double> &targetValues)
{

}

void ANN::getOutput(vector<double> &outputValues) const
{

}
