#include "urdfparser.h"
#include <QDebug>

//konstruktor


bool URDFparser::getFileParsed()
{
    return fileParsed;
}

void URDFparser::setFileParsed(bool value)
{
    fileParsed = value;
}

URDFparser::URDFparser()
{
}

void URDFparser::addInertialElementChildren(int i, QDomElement inertialElement, Inertial* inertial)
{
    if(inertialElement.childNodes().at(i).toElement().tagName() == "origin")
    {
        //origin
        QDomElement originElement = inertialElement.firstChildElement("origin");
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
        inertial->setOrigin(*origin);
    }
    else if (inertialElement.childNodes().at(i).toElement().tagName() == "mass")
    {
        QDomElement massElement = inertialElement.firstChildElement("mass");
        QString massVal = massElement.attribute("value", "");
        Mass* mass = new Mass(massVal.toDouble());
        inertial->setMass(*mass);
    }
    else if (inertialElement.childNodes().at(i).toElement().tagName() == "inertia")
    {
        QDomElement inertiaElement = inertialElement.firstChildElement("inertia");
        QString ixx = inertiaElement.attribute("ixx");
        QString ixy = inertiaElement.attribute("ixy");
        QString ixz = inertiaElement.attribute("ixz");
        QString iyy = inertiaElement.attribute("iyy");
        QString iyz = inertiaElement.attribute("iyz");
        QString izz = inertiaElement.attribute("izz");
        if(ixx==" ") ixx="0";
        if(ixy==" ") ixy="0";
        if(ixz==" ") ixz="0";
        if(iyy==" ") iyy="0";
        if(iyz==" ") iyz="0";
        if(izz==" ") izz="0";
        Inertia* inertia = new Inertia(ixx.toDouble(), ixy.toDouble(), ixz.toDouble(), iyy.toDouble(), iyz.toDouble(), izz.toDouble());
        inertial->setIntertia(*inertia);
    }
}

map<QString, Link> URDFparser::getUsedLinks() const
{
    return usedLinks;
}

void URDFparser::setUsedLinks(const map<QString, Link> &value)
{
    usedLinks = value;
}

void URDFparser::parseChildNodes(QDomElement root, int i)
{
    QDomNode node = root.childNodes().at(i);

    if(node.isElement())
    {
        QDomElement nodeElement = node.toElement();
        if(nodeElement.tagName() == "joint")
        {
            //joint name
            QString name = nodeElement.attribute("name", "noName link");

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
            //link name
            QString name = nodeElement.attribute("name", "noName link");

            //inertial
            Inertial inertial;
            QDomElement inertialElement = nodeElement.firstChildElement("inertial");
            for(int i=0; i<inertialElement.childNodes().count(); i++)
            {
                addInertialElementChildren(i, inertialElement, &inertial);
            }

            //visual
            vector<Visual> visuals;
            QDomNodeList visualNodes = nodeElement.elementsByTagName("visual");
            for(int i=0; i<visualNodes.size(); i++)
            {
                QDomNode visualNode = visualNodes.item(i);
                QDomElement visualElement = visualNode.toElement();
                QString visualName = visualElement.attribute("name", "");

                //origin
                QDomElement originElement = visualNode.firstChildElement("origin");
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

                //geometry
                QDomElement geometryElement = visualNode.firstChildElement("geometry");
                Geometry* geometry = new Geometry();

                    //box
                    QDomElement boxElement = geometryElement.firstChildElement("box");
                    if(boxElement.tagName() != "")
                    {
                        QString sizeText = boxElement.attribute("size", "");
                        QStringList sizeVal = sizeText.split(" ");
                        double x_box = sizeVal[0].toDouble();
                        double y_box = sizeVal[1].toDouble();
                        double z_box = sizeVal[2].toDouble();                        Box* box = new Box(x_box, y_box, z_box);
                        box->setName("box");
                        geometry = new Geometry(*box);
                    }

                    //cylinder
                    QDomElement cylinderElement = geometryElement.firstChildElement("cylinder");
                    if(cylinderElement.tagName()!= "")
                    {
                        QString radiusText = cylinderElement.attribute("radius", "");
                        QString lengthText = cylinderElement.attribute("length", "");
                        double radius = radiusText.toDouble();
                        double length = lengthText.toDouble();
                        Cylinder* cylinder = new Cylinder(radius, length);
                        cylinder->setName("cylinder");
                        geometry = new Geometry(*cylinder);
                    }
                    //sphere
                    QDomElement sphereElement = geometryElement.firstChildElement("sphere");
                    if(sphereElement.tagName()!="")
                    {
                        QString radiusText = sphereElement.attribute("radius", "");
                        double radius = radiusText.toDouble();
                        Sphere* sphere = new Sphere(radius);
                        sphere->setName("sphere");
                        geometry = new Geometry(*sphere);
                    }


                //material
                QDomElement materialElement = visualNode.firstChildElement("material");
                QString materialName = materialElement.attribute("name", "");

                    //color
                    QDomElement colorElement = materialElement.firstChildElement("color");
                    QString colorText = colorElement.attribute("rgba", "");
                    Color* color;
                    double rColor, gColor, bColor, aColor;
                    if(colorText!="")
                    {
                        QStringList rgbaList = colorText.split(" ");
                        rColor = rgbaList[0].toDouble();
                        gColor = rgbaList[1].toDouble();
                        bColor = rgbaList[2].toDouble();
                        aColor = rgbaList[3].toDouble();
                    }
                    else
                    {
                        rColor = 0; gColor = 0; bColor = 0; aColor = 0;
                    }
                    color = new Color(rColor, gColor, bColor, aColor);

                    //texture
                    Texture* texture = new Texture();


                Material* material = new Material(materialName, *color, *texture);

                Visual* visual = new Visual(visualName, *origin, *geometry, *material);
                visuals.push_back(*visual);
            }


            Collision collision;
            Link* link = new Link(name, inertial, visuals, collision);
            QString val  = link->toString();
            qDebug()<<val;
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
    fileParsed = true;
    return 0;
}

bool URDFparser::instanceFlag = false;
URDFparser* URDFparser::instance = NULL;
bool URDFparser::fileParsed = false;
URDFparser* URDFparser::getInstance()
{
    if(!instanceFlag)
    {
       instance = new URDFparser();
       instanceFlag = true;
    }
    return instance;
}
