#include "neuron.h"

Neuron::Neuron(unsigned numOutputs, unsigned neuronIndex)
{
    index = neuronIndex;

    for(unsigned i=0; i<numOutputs; i++)
    {
        outputWeights.push_back(Connection());

    }
}

void Neuron::feedForward(const vector<Neuron> &previousLayer)
{
    //output = f(sum(i)(ii*wi))
    double sum = 0.0;
    unsigned type = 1;

    for(unsigned i = 0; i < previousLayer.size(); i++)
    {
        vector<Connection> outputWeights = previousLayer[i].getOutputWeights();
        sum+= previousLayer[i].getOutputValue() * outputWeights[index].getWeight();
    }

    outputValue = activationFunction(sum, type);
}


double Neuron::activationFunction(double sum, unsigned type)
{
    double output = 0.0;

    switch(type)
    {
    case 0: //sigmoid, aproximation; //original: 1/(1 + exp(-sum))
    {
        output = sum / (1 + abs(sum));
        break;
    }
    case 1: //hyperbolic tangent function
    {
        output = tanh(sum);
        break;
    }
    default:
    {
        output = tanh(sum);
        break;
    }
    }
    return output;
}

//derivative
double Neuron::dActivationFunction(double sum, unsigned type)
{
    double output = 0.0;

    switch(type)
    {
    case 0: //sigmoid, approximation
    {
        output = 1/((1 + abs(sum))*(1 + abs(sum)));
        break;
    }
    case 1: //hyperbolic tangent function
    {
        output = 1 - tanh(sum)*tanh(sum);
        break;
    }
    default:
    {
        output = 1 - tanh(sum)*tanh(sum);
        break;
    }
    }
    return output;
}

double Neuron::getOutputValue() const
{
    return outputValue;
}

void Neuron::setOutputValue(double value)
{
    outputValue = value;
}

vector<Connection> Neuron::getOutputWeights() const
{
    return outputWeights;
}

void Neuron::setOutputWeights(const vector<Connection> &value)
{
    outputWeights = value;
}


