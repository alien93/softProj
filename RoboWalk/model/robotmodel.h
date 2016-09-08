#ifndef ROBOTMODEL_H
#define ROBOTMODEL_H

#include "QString"
#include <iostream>
#include <map>
#include <vector>
#include "joint.h"
#include "model/link.h"
#include "QDebug"

using namespace std;

class RobotModel
{
private:
    QString name;
    map<QString, Joint> joints;
    map<QString, MyLink> links;
    vector<Joint> jointsVector;
    vector<MyLink> linksVector;
    void createBranch(vector<Joint> *retVal, map<QString, Joint> joints, QString jointName);

public:
    RobotModel();
    RobotModel(QString name, map<QString, Joint> joints, map<QString, MyLink> links);
    map<QString, Joint> getJoints() const;
    void setJoints(const map<QString, Joint> &value);
    map<QString, MyLink> getLinks() const;
    void setLinks(const map<QString, MyLink> &value);
    QString getName() const;
    void setName(const QString &value);
    void addJoint(Joint newJoint);
    void addLink(MyLink newLink);
    Joint getJoint(QString name);
    MyLink getLink(QString name);
    vector<Joint> getJointsVector() const;
    void setJointsVector(const vector<Joint> &value);
    vector<MyLink> getLinksVector() const;
    void setLinksVector(const vector<MyLink> &value);
    vector<Joint> sortJoints(map<QString, Joint> map);
    bool containsJoint(vector<Joint> values, Joint j);
};

#endif // ROBOTMODEL_H
