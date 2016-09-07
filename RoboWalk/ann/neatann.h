#ifndef NEATANN_H
#define NEATANN_H

#include <qstring.h>
#include <vector>
#include <map>
#include <qfile.h>
#include <qdebug.h>
#include <qstringlist.h>
#include <math.h>

using namespace std;

const double SLOPE = 4.924273;

enum NodePlacement
{
    HIDDEN = 0,
    INPUT = 1,
    OUTPUT = 2,
    BIAS = 3
};

struct Node
{
    int nodeId;
    NodePlacement nodePlacement;
    double value;
    bool isSet;
};

struct Gene
{
    int inputNodeId;
    int outputNodeId;
    double weight;
};

class NeatAnn
{
private:
    map<int, Node> nodes;
    vector<Gene> genes;
    int noOfNullNodes;
public:
    NeatAnn();
    void parseAnnData(QString filename, vector<double> inputs);
    void run();
    void printOutput();
    double fsigmoid(double x);
    vector<Gene> getGenes() const;
    void setGenes(const vector<Gene> &value);
    map<int, Node> getNodes() const;
    void setNodes(const map<int, Node> &value);
};

#endif // NEATANN_H
