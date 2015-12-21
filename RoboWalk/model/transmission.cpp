#include "transmission.h"

QString Transmission::getName() const
{
    return name;
}

void Transmission::setName(const QString &value)
{
    name = value;
}

TransmissionType Transmission::getType() const
{
    return type;
}

void Transmission::setType(const TransmissionType &value)
{
    type = value;
}

vector<TransmissionJoint> Transmission::getJoint() const
{
    return joint;
}

void Transmission::setJoint(const vector<TransmissionJoint> &value)
{
    joint = value;
}

vector<Actuator> Transmission::getActuator() const
{
    return actuator;
}

void Transmission::setActuator(const vector<Actuator> &value)
{
    actuator = value;
}

Transmission::Transmission()
{

}

Transmission::Transmission(QString name, TransmissionType type, vector<TransmissionJoint> joint, vector<Actuator> actuator)
{
    this->name = name;
    this->type = type;
    this->joint = joint;
    this->actuator = actuator;
}
