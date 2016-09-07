#include "neatann.h"

NeatAnn::NeatAnn()
{
    noOfNullNodes = 0;
}

void NeatAnn::parseAnnData(QString filename, vector<double> inputs)
{

    int counter = 0;

    //loading file
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Failed to open file";
        return;
    }
    else
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            QStringList list = line.split(" ");

            if(list[0] == "node")
            {
                Node n;
                n.nodeId = list[1].toInt();
                n.nodePlacement = static_cast<NodePlacement>(list[4].toInt());
                if(n.nodePlacement == NodePlacement::INPUT)
                {
                    n.value = inputs.at(counter++);
                    n.isSet = true;
                }
                else if (n.nodePlacement == NodePlacement::BIAS)
                {
                    n.value = 1.0;
                    n.isSet = true;
                }
                else
                {
                    n.isSet = false;
                    noOfNullNodes++;
                }
                nodes.insert(pair<int, Node>(n.nodeId, n));
            }
            else if(list[0] == "gene")
            {
                Gene g;
                g.inputNodeId = list[2].toInt();
                g.outputNodeId = list[3].toInt();
                g.weight = list[4].toDouble();
                genes.push_back(g);
            }
        }

        file.close();
    }
}

void NeatAnn::run()
{
    bool definedValues = true;
    double sumOfOutputs = 0;

    while(noOfNullNodes>0)      //while there are nodes with unset values (null values)
    {
        for(vector<Gene>::iterator it = genes.begin(); it!= genes.end(); it++)             //for each gene check if input values exist
        {
            Gene gene = *it;
            definedValues = true;
            sumOfOutputs = 0;

            for(vector<Gene>::iterator it1 = genes.begin(); it1!= genes.end(); it1++)
            {
                Gene gene1 = *it1;
                if(gene.outputNodeId == gene1.outputNodeId &&
                   nodes.at(gene1.inputNodeId).isSet == true && nodes.at(gene.outputNodeId).isSet == false)
                {
                    sumOfOutputs+=nodes.at(gene1.inputNodeId).value * gene1.weight;
                }
                else if(gene.outputNodeId == gene1.outputNodeId && nodes.at(gene1.inputNodeId).isSet == false)
                {
                    definedValues = false;
                    break;
                }
            }

            if(definedValues)                   //all values for output nodes are defined, do the calculations
            {
                double result = fsigmoid(sumOfOutputs);
                nodes.at(gene.outputNodeId).value = result;
                nodes.at(gene.outputNodeId).isSet = true;
                --noOfNullNodes;
                break;
            }
        }
    }
    printOutput();
}

double NeatAnn::fsigmoid(double x)
{
    return 1/(1 + exp(-SLOPE*x));
}

void NeatAnn::printOutput()
{
    qDebug()<<"Printing output values from neat ann";
    qDebug()<<"---------------------------------------";
    for(map<int, Node>::iterator it=nodes.begin(); it!=nodes.end(); it++)
    {
        Node node = it->second;
        if(node.nodePlacement == NodePlacement::OUTPUT)
        {
            //print output values
            qDebug()<<node.value;
        }
    }
    qDebug()<<"---------------------------------------";
}

vector<Gene> NeatAnn::getGenes() const
{
    return genes;
}

void NeatAnn::setGenes(const vector<Gene> &value)
{
    genes = value;
}


map<int, Node> NeatAnn::getNodes() const
{
    return nodes;
}

void NeatAnn::setNodes(const map<int, Node> &value)
{
    nodes = value;
}

