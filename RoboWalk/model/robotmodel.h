#ifndef ROBOTMODEL_H
#define ROBOTMODEL_H

#include "QString"
#include <iostream>
#include <map>
#include <vector>
#include "joint.h"
#include "link.h"

using namespace std;

class RobotModel
{
private:
    QString name;
    map<QString, Joint> joints;
    map<QString, Link> links;
    vector<Joint> jointsVector;
    vector<Link> linksVector;
public:
    RobotModel();
    RobotModel(QString name, map<QString, Joint> joints, map<QString, Link> links);
    map<QString, Joint> getJoints() const;
    void setJoints(const map<QString, Joint> &value);
    map<QString, Link> getLinks() const;
    void setLinks(const map<QString, Link> &value);
    QString getName() const;
    void setName(const QString &value);
    void addJoint(Joint newJoint);
    void addLink(Link newLink);
    Joint getJoint(QString name);
    Link getLink(QString name);
    vector<Joint> getJointsVector() const;
    void setJointsVector(const vector<Joint> &value);
    vector<Link> getLinksVector() const;
    void setLinksVector(const vector<Link> &value);
};

#endif // ROBOTMODEL_H
