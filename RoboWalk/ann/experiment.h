#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <random>
#include <qdebug.h>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <neat/population.h>

using namespace std;

using namespace NEAT;

class Experiment
{
public:
    Experiment();
    void generateTestData();
    Population* roboWalk_test(int gens);
    bool roboWalk_evaluate(Organism* org);
    int roboWalk_epoch(Population* pop, int generation, char *filename, int &winnernum, int &winnergenes, int &winnernodes);
    int roboWalk_runInput(Network* net, int maxSteps, int thresh);
    //void roboWalk_walk(int action, float *x, float )
};

#endif // EXPERIMENT_H
