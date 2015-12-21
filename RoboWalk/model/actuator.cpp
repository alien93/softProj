#include "actuator.h"

QString Actuator::getName() const
{
    return name;
}

void Actuator::setName(const QString &value)
{
    name = value;
}

vector<MechanicalReduction> Actuator::getMechanicalReduction() const
{
    return mechanicalReduction;
}

void Actuator::setMechanicalReduction(const vector<MechanicalReduction> &value)
{
    mechanicalReduction = value;
}

Actuator::Actuator()
{

}

Actuator::Actuator(QString name, vector<MechanicalReduction> mechanicalReductinon)
{
    this->name = name;
    this->mechanicalReduction = mechanicalReductinon;
}
