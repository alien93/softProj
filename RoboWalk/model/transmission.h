#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <QString>
#include "transmissiontype.h"
#include "transmissionjoint.h"
#include "actuator.h"
#include <iostream>
#include <vector>

using namespace std;

class Transmission
{
private:
    QString name;
    TransmissionType type;
    vector<TransmissionJoint> joint;
    vector<Actuator> actuator;
public:
    Transmission();
    Transmission(QString name, TransmissionType type,
                 vector<TransmissionJoint> joint, vector<Actuator> actuator);


    QString getName() const;
    void setName(const QString &value);
    TransmissionType getType() const;
    void setType(const TransmissionType &value);
    vector<TransmissionJoint> getJoint() const;
    void setJoint(const vector<TransmissionJoint> &value);
    vector<Actuator> getActuator() const;
    void setActuator(const vector<Actuator> &value);
};

#endif // TRANSMISSION_H
