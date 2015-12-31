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

            //origin
            QDomElement originElement = nodeElement.firstChildElement("origin");
            QString rpy = originElement.attribute("rpy", "");
            QString xyz = originElement.attribute("xyz", "");
            double x, y, z, r, p, yy;
            if(xyz!="")
            {
                QStringList xyz_data = xyz.split(" ");
                x = xyz_data[0].toDouble();
                y = xyz_data[1].toDouble();
                z = xyz_data[2].toDouble();
            }
            else
            {
                x=0; y=0; z=0;
            }
            if(rpy!="")
            {
                QStringList rpy_data = rpy.split(" ");
                r = rpy_data[0].toDouble();
                p = rpy_data[1].toDouble();
                yy = rpy_data[2].toDouble();
            }
            else
            {
                r=0; p=0; yy=0;
            }
            Origin* origin = new Origin(x, y, z, r, p, yy);

            //parent
            QDomElement parentElement = nodeElement.firstChildElement("parent");
            QString linkName = parentElement.attribute("link", "");
            Parent* parent = new Parent(linkName);

            //child
            QDomElement childElement = nodeElement.firstChildElement("child");
            QString childName = childElement.attribute("link", "");
            Child* child = new Child(childName);


            //axis
            QDomElement axisElement = nodeElement.firstChildElement("axis");
            QString rpy_axis = axisElement.attribute("rpy", "");
            QString xyz_axis = axisElement.attribute("xyz", "");
            double x1, y1, z1, r1, p1, yy1;
            if(xyz_axis!="")
            {
                QStringList xyz_dataAxis = xyz.split(" ");
                x1 = xyz_dataAxis[0].toDouble();
                y1 = xyz_dataAxis[1].toDouble();
                z1 = xyz_dataAxis[2].toDouble();
            }
            else
            {
                x1=1; y1=0; z1=0;
            }
            if(rpy_axis!="")
            {
                QStringList rpy_dataAxis = rpy.split(" ");
                r1 = rpy_dataAxis[0].toDouble();
                p1 = rpy_dataAxis[1].toDouble();
                yy1 = rpy_dataAxis[2].toDouble();
            }
            else
            {
                r1=0; p1=0; yy1=0;
            }
            Axis* axis = new Axis(x1, y1, z1, r1, p1, yy1);

            //calibration
            QDomElement calibrationElement = nodeElement.firstChildElement("calibration");
            QString rising = calibrationElement.attribute("rising", "");
            QString falling = calibrationElement.attribute("falling", "");
            Calibration* calibration = new Calibration(rising.toDouble(), falling.toDouble());

            //dynamics
            QDomElement dynamicsElement = nodeElement.firstChildElement("dynamics");
            QString damping = dynamicsElement.attribute("damping", "");
            QString friction = dynamicsElement.attribute("friction", "");
            Dynamics* dynamics = new Dynamics(damping.toDouble(), friction.toDouble());

            //limit
            QDomElement limitElement = nodeElement.firstChildElement("limit");
            QString lower = limitElement.attribute("lower", "");
            QString upper = limitElement.attribute("upper", "");
            QString effort = limitElement.attribute("effort", "");
            QString velocity = limitElement.attribute("velocity", "");
            Limit* limit = new Limit(lower.toDouble(), upper.toDouble(), effort.toDouble(), velocity.toDouble());

            //mimic
            QDomElement mimicElement = nodeElement.firstChildElement("mimic");
            QString jointMimic = mimicElement.attribute("joint", "");
            QString multiplier = mimicElement.attribute("multiplier", "");
            QString offset = mimicElement.attribute("offset", "");
            if(multiplier == "") multiplier = "1";
            if(offset == "") offset = "0";
            Mimic* mimic = new Mimic(jointMimic, multiplier.toDouble(), offset.toDouble());

            //safety controller
            QDomElement safetyControllerElement = nodeElement.firstChildElement("safety_controller");
            QString soft_lower_limit = safetyControllerElement.attribute("soft_lower_limit", "");
            QString soft_upper_limit = safetyControllerElement.attribute("soft_upper_limit", "");
            QString k_position = safetyControllerElement.attribute("k_position", "");
            QString k_velocity = safetyControllerElement.attribute("k_velocity", "");
            if(soft_lower_limit == "") soft_lower_limit = "0";
            if(soft_upper_limit == "") soft_upper_limit = "0";
            if(k_position == "") k_position = "0";
            SafetyController* safetyController = new SafetyController(soft_lower_limit.toDouble(),
                                                                      soft_upper_limit.toDouble(),
                                                                      k_position.toDouble(),
                                                                      k_velocity.toDouble());

            Joint* joint = new Joint(name, type, *origin, *parent, *child,
                                     *axis,*calibration,*dynamics,*limit,
                                     *mimic, *safetyController);
            QString val  = joint->toString();
            qDebug()<<val;
            rm.addJoint(*joint);
        }
        else if(nodeElement.tagName() == "link")
        {
            QString name = nodeElement.attribute("name", "noName link");
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
