#include "connection.h"

double Connection::getWeight() const
{
    return weight;
}

void Connection::setWeight(double value)
{
    weight = value;
}

double Connection::getDWeight() const
{
    return dWeight;
}

void Connection::setDWeight(double value)
{
    dWeight = value;
}

Connection::Connection()
{
    weight = randomWeight();
}


double Connection::randomWeight()
{
    return rand() / double(RAND_MAX);   //returns value between 0.0 and 1.0
}

