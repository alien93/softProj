#ifndef ANN_H
#define ANN_H

#include <vector>
#include "neuron.h"
#include <assert.h>
#include <QDebug>

using namespace std;

class ANN
{
private:
    double annError;
    vector<vector<Neuron>> layers;
public:
    ANN(const vector<unsigned> &neuronsPerLayer);
    void feedForward(const vector<double> &inputValues);
    void backPropagation(const vector<double> &targetValues);
    void getOutput(vector<double> &outputValues) const;
};

#endif // ANN_H
