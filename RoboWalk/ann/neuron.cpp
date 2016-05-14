#include "neuron.h"

Neuron::Neuron(unsigned numOutputs, unsigned neuronIndex)
{
    index = neuronIndex;

    eta = 0.15; //overall learning rate
    alpha = 0.5; //momentum, multiplier of the last deltaWeight


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
        sum+= previousLayer[i].getOutputValue() * previousLayer[i].outputWeights[index].getWeight();
    }

    outputValue = activationFunction(sum, type);
}


vector<Connection> Neuron::getInputWeights() const
{
    return inputWeights;
}

void Neuron::setInputWeights(const vector<Connection> &value)
{
    inputWeights = value;
}

void Neuron::updateInputWeights(vector<Neuron> &previousLayer)
{
    for(unsigned i=0; i<previousLayer.size(); i++)
    {
        Neuron &neuron = previousLayer[i];
        double oldDWeight = neuron.outputWeights[index].getDWeight();
        //overall learning rate (eta) * previous layer's neuron's output val * gradient + momentum calculation(momentum rate)
        double newDWeight = eta * neuron.getOutputValue() * gradient + alpha * oldDWeight;
        neuron.outputWeights[index].setDWeight(newDWeight);
        neuron.outputWeights[index].setWeight(neuron.outputWeights[index].getWeight() + newDWeight);
    }
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

double Neuron::dSumWeights(const vector<Neuron> &nextLayer) const
{
    double dSumWeights = 0.0;

    for(unsigned i=0; i<nextLayer.size() - 1; i++)
    {
        //Connection connection = outputWeights[i];
        dSumWeights += outputWeights[i].getWeight() * nextLayer[i].gradient;
    }

    return dSumWeights;
}

void Neuron::setGradient(double targetValue)
{
    double delta = targetValue - outputValue;
    gradient = delta * dActivationFunction(outputValue, 1);
}

double Neuron::setHiddenGradients(const vector<Neuron> &layer)
{
    //sum of the derivative of the weights of the next layer
    double dSum = dSumWeights(layer);
    gradient = dSum * dActivationFunction(outputValue, 1);
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


