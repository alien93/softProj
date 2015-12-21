#include "modelstate.h"

QString ModelState::getModel() const
{
    return model;
}

void ModelState::setModel(const QString &value)
{
    model = value;
}

float ModelState::getTimeStamp() const
{
    return timeStamp;
}

void ModelState::setTimeStamp(float value)
{
    timeStamp = value;
}

vector<JointState> ModelState::getJointState() const
{
    return jointState;
}

void ModelState::setJointState(const vector<JointState> &value)
{
    jointState = value;
}

ModelState::ModelState()
{

}

ModelState::ModelState(QString model, float timeStamp, vector<JointState> jointState)
{
    this->model = model;
    this->timeStamp = timeStamp;
    this->jointState = jointState;
}
