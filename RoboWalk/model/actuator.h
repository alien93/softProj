#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <QString>
#include "mechanicalreduction.h"
#include <iostream>
#include <vector>

using namespace std;

class Actuator
{
private:
    QString name;
    vector<MechanicalReduction> mechanicalReduction;
public:
    Actuator();
    Actuator(QString name, vector<MechanicalReduction> mechanicalReductinon);

    QString getName() const;
    void setName(const QString &value);
    vector<MechanicalReduction> getMechanicalReduction() const;
    void setMechanicalReduction(const vector<MechanicalReduction> &value);
};

#endif // ACTUATOR_H
