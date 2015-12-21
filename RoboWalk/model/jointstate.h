#ifndef JOINTSTATE_H
#define JOINTSTATE_H

#include <QString>
#include <iostream>
#include <vector>

using namespace std;


class JointState
{
private:
    QString joint;
    vector<float> position; //position for each degree of freedom of this joint
    vector<float> velocity; //velocity for each degree of freedom of this joint
    vector<float> effort; //effort for each degree of freedom of this joint
public:
    JointState();
    JointState(QString joint, vector<float> position,
               vector<float> velocity, vector<float> effort);

    QString getJoint() const;
    void setJoint(const QString &value);
    vector<float> getPosition() const;
    void setPosition(const vector<float> &value);
    vector<float> getVelocity() const;
    void setVelocity(const vector<float> &value);
    vector<float> getEffort() const;
    void setEffort(const vector<float> &value);
};

#endif // JOINTSTATE_H
