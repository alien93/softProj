#include "robotmodel.h"

vector<Joint> RobotModel::getJointsVector() const
{
    return jointsVector;
}

void RobotModel::setJointsVector(const vector<Joint> &value)
{
    jointsVector = value;
}

vector<MyLink> RobotModel::getLinksVector() const
{
    return linksVector;
}

void RobotModel::setLinksVector(const vector<MyLink> &value)
{
    linksVector = value;
}

RobotModel::RobotModel(){}
RobotModel::RobotModel(QString name, map<QString, Joint> joints, map<QString, MyLink> links)
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
map<QString, MyLink> RobotModel::getLinks() const
{
    return links;
}
void RobotModel::setLinks(const map<QString, MyLink> &value)
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
    jointsVector.push_back(newJoint);
}
void RobotModel::addLink(MyLink newLink)
{
    links[newLink.getName()] = newLink;
    linksVector.push_back(newLink);
}
Joint RobotModel::getJoint(QString name)
{
    return joints[name];
}
MyLink RobotModel::getLink(QString name)
{
    return links[name];
}

vector<Joint> RobotModel::sortJoints(map<QString, Joint> joints)
{
    vector<Joint> retVal;
    /*
     * INPUT:
     * base_link
     * upper_left_leg
     *
     * base_link
     * upper_right_leg
     *
     * upper_left_leg
     * lower_left_leg
     *
     * upper_right_leg
     * lower_right_leg
     *
     * upper_left_leg
     * something_something
     *
     *
     * OUTPUT:
     * base_link
     * upper_left_leg
     *
     * upper_left_leg
     * lower_left_leg
     *
     * upper_left_leg
     * something_something
     *
     * base_link
     * upper_right_leg
     *
     * upper_right_leg
     * lower_right_leg
     *
     */

    vector<QString> parentNodes = {"base_link"};   //base_link is a mandatory link

    for(auto it=joints.begin(); it!=joints.end(); it++)
    {
        QString parent = parentNodes.back();
        if(it->second.getParent().getLink() == parent)
        {
            createBranch(&retVal, joints, it->first);
        }
    }
    return retVal;
}

bool RobotModel::containsJoint(vector<Joint> values, Joint j)
{
    bool retVal = false;
    for(uint i=0; i<values.size(); i++)
    {
        if(values.at(i).getName() == j.getName())
        {
            retVal =  true;
        }
    }
    return retVal;
}

void RobotModel::createBranch(vector<Joint> *retVal, map<QString, Joint> joints, QString jointName)
{
    vector<QString> childNodes = {joints[jointName].getChild().getLink()};  //LIFO
    retVal->push_back(joints[jointName]);
    QString parentNode = childNodes.back();
    for(auto it=joints.begin(); it!=joints.end(); it++)
    {
        if(it->second.getParent().getLink() == parentNode)
        {
            createBranch(retVal, joints, it->first);
        }
    }
}


