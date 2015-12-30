#include "robotmodel.h"

RobotModel::RobotModel(){}
RobotModel::RobotModel(QString name, map<QString, Joint> joints, map<QString, Link> links)
{
    this->name = name;
    this->joints = joints;
    this->links = links;
}
map<QString, Joint> RobotModel::getJoints() const
{
    return joints;
}
void RobotModel::setJoints(const map<QString, Joint> &value)
{
    joints = value;
}
map<QString, Link> RobotModel::getLinks() const
{
    return links;
}
void RobotModel::setLinks(const map<QString, Link> &value)
{
    links = value;
}
QString RobotModel::getName() const
{
    return name;
}
void RobotModel::setName(const QString &value)
{
    this->name = value;
}
void RobotModel::addJoint(Joint newJoint)
{
    joints[newJoint.getName()] = newJoint;
}
void RobotModel::addLink(Link newLink)
{
    links[newLink.getName()] = newLink;
}
Joint RobotModel::getJoint(QString name)
{
    return joints[name];
}
Link RobotModel::getLink(QString name)
{
    return links[name];
}
