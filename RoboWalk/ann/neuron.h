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
    vector<Connection> inputWeights;
    vector<Connection> outputWeights;
    double gradient;
    double alpha;
    double eta;

    double activationFunction(double sum, unsigned type);  //type: 0-sigmoid, 1-hyperbolic tangent function
    double dActivationFunction(double sum, unsigned type);

    double dSumWeights(const vector<Neuron> &nextLayer) const;
public:
    Neuron(unsigned numOutputs, unsigned neuronIndex);
    void feedForward(const vector<Neuron> &previousLayer);

    double getOutputValue() const;
    void setOutputValue(double value);
    vector<Connection> getOutputWeights() const;
    void setOutputWeights(const vector<Connection> &value);
    vector<Connection> getInputWeights() const;
    void setInputWeights(const vector<Connection> &value);
    void updateInputWeights(vector<Neuron> &previousLayer);


    //gradients
    void setGradient(double targetValue);
    double setHiddenGradients(const vector<Neuron> &layer);
};

#endif // NEURON_H
