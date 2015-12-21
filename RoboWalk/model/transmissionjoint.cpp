#include "transmissionjoint.h"

QString TransmissionJoint::getName() const
{
    return name;
}

void TransmissionJoint::setName(const QString &value)
{
    name = value;
}

vector<HardwareInterface> TransmissionJoint::getHardwareInterface() const
{
    return hardwareInterface;
}

void TransmissionJoint::setHardwareInterface(const vector<HardwareInterface> &value)
{
    hardwareInterface = value;
}

TransmissionJoint::TransmissionJoint()
{

}

TransmissionJoint::TransmissionJoint(QString name, vector<HardwareInterface> hardwareInterface)
{
    this->name = name;
    this->hardwareInterface = hardwareInterface;
}
