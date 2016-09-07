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
        }

        //set bias node's output value
        layers.back().back().setOutputValue(1.0);
    }
}

void ANN::feedForward(const vector<double> &inputValues)
{
    assert(inputValues.size() == layers[0].size() - 1 &&
           "Number of input values is different than the number"
           "of nodes in the input layer. Terminating.");

    //put input values in input neurons
    for(unsigned i=0; i<inputValues.size(); i++)
    {
        layers[0][i].setOutputValue(inputValues[i]);
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

//!calculates error, gradients and updates connection weights
void ANN::backPropagation(const vector<double> &targetValues)
{
    //RMSE = sqrt(1/n*sum(i-n)sqr(target(i)-actual(i))
    double sum = 0.0;
    annError = 0.0;
    vector<Neuron> &outputLayer = layers.back();
    unsigned numOutputs = outputLayer.size() - 1;

    //for all neurons in ann's output layer (- bias)
    for(unsigned i=0; i<numOutputs; i++)
    {
        double target = targetValues[i];                 //target value for the neuron
        double actual = outputLayer[i].getOutputValue(); //get the actual output value of the neuron
        sum += pow(target - actual, 2);                  //sum of the errors
    }
    annError = sqrt(sum/numOutputs);

    //output gradients
    for(unsigned i=0; i<numOutputs; i++)
    {
        outputLayer[i].setGradient(targetValues[i]);
    }

    //hidden layer gradients

    unsigned idxLastHiddenLayer = layers.size() - 2;
    //for all hidden layers
    for(unsigned i=idxLastHiddenLayer; i>0; --i)
    {
        vector<Neuron> &hiddenLayer = layers[i];
        vector<Neuron> &nextLayer = layers[i + 1];

        //for all neurons in the hidden layer
        for(unsigned j=0; j<hiddenLayer.size(); j++)
        {
            hiddenLayer[j].setHiddenGradients(nextLayer);
        }

    }

    //update the weights

    //for all layers (- the input layer)
    unsigned idxOutputLayer = layers.size() - 1;
    for(unsigned i = idxOutputLayer; i > 0; i--)
    {
        vector<Neuron> &layer = layers[i];
        vector<Neuron> &previousLayer = layers[i - 1];

        //for each neuron (- bias)
        for(unsigned j=0; j<layer.size() - 1; j++)
        {
            layer[j].updateInputWeights(previousLayer);
        }
    }
}

void ANN::getOutput(vector<double> &outputValues) const
{
    outputValues.clear();

    for(unsigned i=0; i<layers.back().size() -1; i++)
    {
        outputValues.push_back(layers.back()[i].getOutputValue());
    }
}
