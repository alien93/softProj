#ifndef MODELSTATE_H
#define MODELSTATE_H

#include <QString>
#include "jointstate.h"
#include <iostream>
#include <vector>

using namespace std;

class ModelState
{
private:
    QString model; //the name of the model in corresponding urdf
    float timeStamp; //time stamp of this state in seconds
    vector<JointState> jointState;
public:
    ModelState();
    ModelState(QString model, float timeStamp, vector<JointState> jointState);


    QString getModel() const;
    void setModel(const QString &value);
    float getTimeStamp() const;
    void setTimeStamp(float value);
    vector<JointState> getJointState() const;
    void setJointState(const vector<JointState> &value);
};

#endif // MODELSTATE_H
