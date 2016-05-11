#ifndef NEURON_H
#define NEURON_H

#include "connection.h"
#include <vector>
#include <cmath>

using namespace std;

class Neuron
{
private:
    unsigned index;     //neuron's index
    double outputValue;
    vector<Connection> outputWeights;

    double activationFunction(double sum, unsigned type);  //type: 0-sigmoid, 1-hyperbolic tangent function
    double dActivationFunction(double sum, unsigned type);
public:
    Neuron(unsigned numOutputs, unsigned neuronIndex);
    void feedForward(const vector<Neuron> &previousLayer);

    double getOutputValue() const;
    void setOutputValue(double value);
    vector<Connection> getOutputWeights() const;
    void setOutputWeights(const vector<Connection> &value);
};

#endif // NEURON_H
