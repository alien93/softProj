#ifndef CONNECTION_H
#define CONNECTION_H

#include <cstdlib>
#include <QDebug>

class Connection
{
private:
    double weight;
    double dWeight; //for momentum
public:
    Connection();
    double randomWeight();
    double getWeight() const;
    void setWeight(double value);
    double getDWeight() const;
    void setDWeight(double value);
};

#endif // CONNECTION_H
