#include "jointstate.h"

QString JointState::getJoint() const
{
    return joint;
}

void JointState::setJoint(const QString &value)
{
    joint = value;
}

vector<float> JointState::getPosition() const
{
    return position;
}

void JointState::setPosition(const vector<float> &value)
{
    position = value;
}

vector<float> JointState::getVelocity() const
{
    return velocity;
}

void JointState::setVelocity(const vector<float> &value)
{
    velocity = value;
}

vector<float> JointState::getEffort() const
{
    return effort;
}

void JointState::setEffort(const vector<float> &value)
{
    effort = value;
}

JointState::JointState()
{
    
}

JointState::JointState(QString joint, vector<float> position, vector<float> velocity, vector<float> effort)
{
    this->joint = joint;
    this->position = position;
    this->velocity = velocity;
    this->effort = effort;
}
