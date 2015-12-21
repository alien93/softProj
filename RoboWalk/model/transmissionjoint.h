#ifndef TRANSMISSIONJOINT_H
#define TRANSMISSIONJOINT_H

#include <iostream>
#include <vector>
#include <QString>
#include "hardwareinterface.h"

using namespace std;

class TransmissionJoint
{
private:
    QString name;
    vector<HardwareInterface> hardwareInterface;
public:
    TransmissionJoint();
    TransmissionJoint(QString name, vector<HardwareInterface> hardwareInterface);

    QString getName() const;
    void setName(const QString &value);
    vector<HardwareInterface> getHardwareInterface() const;
    void setHardwareInterface(const vector<HardwareInterface> &value);
};

#endif // TRANSMISSIONJOINT_H
