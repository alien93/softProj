#include "urdfparser.h"
#include <QDebug>

//konstruktor
URDFparser::URDFparser()
{
}

void URDFparser::parseChildNodes(QDomElement root, int i)
{
    QDomNode node = root.childNodes().at(i);

    if(node.isElement())
    {
        QDomElement nodeElement = node.toElement();
        if(nodeElement.tagName() == "joint")
        {
            QString name = nodeElement.attribute("name", "noName link");    //naziv joint-a

            //dobavljanje tipa joint-a
            //revolute, continuous, prismatic, fixeed, floating, planar
            Types type;
            if(nodeElement.attribute("type", "") == "fixed")
            {
                type = fixeed;
            }
            else if(nodeElement.attribute("type", "") == "revolute")
            {
                type = revolute;
            }
            else if(nodeElement.attribute("type", "") == "continuous")
            {
                type = continuous;
            }
            else if(nodeElement.attribute("type", "") == "prismatic")
            {
                type = prismatic;
            }
            else if(nodeElement.attribute("type", "") == "floating")
            {
                type = floating;
            }
            else if(nodeElement.attribute("type", "") == "planar")
            {
                type = planar;
            }

            Origin origin;
            QDomElement originElement = nodeElement.firstChildElement("origin");

            Parent parent;
            Child child;
            Axis axis;
            Calibration calibration;
            Dynamics dynamics;
            Limit limit;
            Mimic mimic;
            SafetyController safetyController;
            Joint* joint = new Joint(name, type, origin, parent, child,
                                     axis,calibration,dynamics,limit,
                                     mimic,safetyController);
            rm.addJoint(*joint);
        }
        else if(nodeElement.tagName() == "link")
        {
            QString name = nodeElement.attribute("name", "noName link");
            qDebug()<<name;
            Inertial inertial;
            vector<Visual> visuals;
            Collision collision;
            Link* link = new Link(name, inertial, visuals, collision);
            rm.addLink(*link);
        }
    }
}

int URDFparser::parseURDF(QString filename)
{
    QDomDocument document;

    //loading file
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Failed to open file";
        return -1;
    }
    else
    {
        if(!document.setContent(&file))
        {
            qDebug()<<"Failed to load document";
            return -1;
        }
        file.close();
    }

    //root element
    QDomElement root = document.firstChildElement();
    QString roboName = root.attribute("name", "roboName not set");
    rm.setName(roboName);
    for(int i=0; i<root.childNodes().count(); i++)
    {
        parseChildNodes(root, i);
    }
    return 0;
}

bool URDFparser::instanceFlag = false;
URDFparser* URDFparser::instance = NULL;
URDFparser* URDFparser::getInstance()
{
    if(!instanceFlag)
    {
       instance = new URDFparser();
       instanceFlag = true;
    }
    return instance;
}
