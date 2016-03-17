#include "robotmodel.h"

vector<Joint> RobotModel::getJointsVector() const
{
    return jointsVector;
}

void RobotModel::setJointsVector(const vector<Joint> &value)
{
    jointsVector = value;
}

vector<Link> RobotModel::getLinksVector() const
{
    return linksVector;
}

void RobotModel::setLinksVector(const vector<Link> &value)
{
    linksVector = value;
}

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
    jointsVector.push_back(newJoint);
}
void RobotModel::addLink(Link newLink)
{
    links[newLink.getName()] = newLink;
    linksVector.push_back(newLink);
}
Joint RobotModel::getJoint(QString name)
{
    return joints[name];
}
Link RobotModel::getLink(QString name)
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




 /*   map<QString, vector<QString> > dictionary;
    vector<QString> nodesToDo;
    bool parentFound = false;

    //populating dictionary (initialization)
    for(auto it=joints.begin(); it!=joints.end(); it++)
    {
        Joint j = it->second;
        if(!dictionary.count(j.getParent().getLink()))  //if link does not exist
        {
            //add Link to the dictionary
            dictionary[j.getParent().getLink()] = {};
        }
        if(!dictionary.count(j.getChild().getLink()))
        {
            dictionary[j.getChild().getLink()] = {};
        }
    }

    //adding values to the dictionary
    for(auto it=dictionary.begin(); it!=dictionary.end(); it++)
    {
        for(auto it2=joints.begin(); it2!=joints.end(); it2++)
        {
            QString a = it->first;
            QString b = it2->second.getParent().getLink();
            if(it->first == it2->second.getParent().getLink())
            {
                it->second.push_back(it2->second.getChild().getLink());
            }
        }
    }

    //sorting dictionary, creating Robot State
    for(auto it=dictionary.begin();it!=dictionary.end();)
    {
        QString parentNode = it->first;
        for(auto it2=dictionary.begin();it2!=dictionary.end(); it2++)
        {
            vector<QString> childNodes = it2->second;
            if(find(childNodes.begin(), childNodes.end(), parentNode) != childNodes.end())
            {
                //childNodes vector contains parentNode
                break;
            }
            else
            {
                //childNodes vector does not contain parentNode
                //parentNode is a possible node
                if(it2==--dictionary.end())   //a node that has no parent
                {
                    for(auto it3=joints.begin(); it3!=joints.end(); it3++)
                    {
                        QString parentLink = it3->second.getParent().getLink();
                        if(parentNode == parentLink)
                        {
                            if(!containsJoint(retVal, it3->second))
                            {
                                retVal.push_back(it3->second);
                                parentNode = it3->second.getChild().getLink();
                                break;
                            }
                        }
                    }
                    parentFound = true;
                }
            }
        }

        if(parentFound)
        {
            dictionary.erase(it++);
            parentFound = false;
        }
        else
        {
            ++it;
        }
    }
*/

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
   // QString parentNode = joints[jointName].getParent().getLink();
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


