#include "link.h"

vector<Visual> Link::getVisual() const
{
    return visual;
}

void Link::setVisual(const vector<Visual> &value)
{
    visual = value;
}

Link::Link()
{

}

Link::Link(QString name, Inertial inertial, vector<Visual> visual, Collision collision)
{
    this->name = name;
    this->inertial = inertial;
    this->visual = visual;
    this->collision = collision;
}

QString Link::getName() const
{
    return name;
}

void Link::setName(const QString &value)
{
    name = value;
}

Inertial Link::getInertial() const
{
    return inertial;
}

void Link::setInertial(const Inertial &value)
{
    inertial = value;
}



Collision Link::getCollision() const
{
    return collision;
}

void Link::setCollision(const Collision &value)
{
    collision = value;
}

QString Link::toString()
{
    QString retVal = "**************************************\n LINK: \n name: " + name + "\n" +
                     "Inertial: \n\n Origin: \n" +
                     "  xyz: " + QString::number(inertial.getOrigin().getXyz_x()) + "," + QString::number(inertial.getOrigin().getXyz_y()) + "," + QString::number(inertial.getOrigin().getXyz_z()) + "\n" +
                     "  rpyL " + QString::number(inertial.getOrigin().getRpy_r()) + "," + QString::number(inertial.getOrigin().getRpy_p()) + "," + QString::number(inertial.getOrigin().getRpy_y()) +
                     "\n + Mass: " + QString::number(inertial.getMass().getValue()) +
                     "\nInertia: \n ixx: " + QString::number(inertial.getIntertia().getIxx()) +
                     "\nixy: " + QString::number(inertial.getIntertia().getIxy()) +
                     "\nixz: " + QString::number(inertial.getIntertia().getIxz()) +
                     "\niyy: " + QString::number(inertial.getIntertia().getIyy()) +
                     "\niyz: " + QString::number(inertial.getIntertia().getIyz()) +
                     "\nizz: " + QString::number(inertial.getIntertia().getIzz()) + "\n";
     for(unsigned i=0; i<visual.size(); i++)
     {
         retVal += "\n\nVisual:\nName:" + ((Visual)(visual.at(i))).getName() + "\n";
         retVal += "Origin: \n";
         retVal += "xyz: " + QString::number(((Visual)(visual.at(i))).getOrigin().getXyz_x()) + "," +
                   QString::number(((Visual)(visual.at(i))).getOrigin().getXyz_y()) + "," +
                  QString::number(((Visual)(visual.at(i))).getOrigin().getXyz_z()) + "\n" +
                   "rpy: " + QString::number(((Visual)(visual.at(i))).getOrigin().getRpy_r()) + "," +
                   QString::number(((Visual)(visual.at(i))).getOrigin().getRpy_p()) + "," +
                   QString::number(((Visual)(visual.at(i))).getOrigin().getRpy_y()) + "\n\n";
         retVal += "Geometry: \n";
         AbstractObject ao;
         ao = ((Visual)(visual.at(i))).getGeometry().getObject();
         QString geoName = ao.getName();
         retVal +=  "Object name:" + geoName;
         if(geoName == "cylinder")
         {
               retVal += "\nName: " +((Cylinder)ao).getName();
               retVal += "\nLength: " + QString::number(((Cylinder)ao).getLength());
               retVal += "\nRadius: " + QString::number(((Cylinder)ao).getRadius()) + "\n";
         }
         else if(geoName == "box")
         {
             retVal += "\nName: " +((Box)ao).getName();
             retVal += "\nWidth: " + QString::number(((Box)ao).getWidth());
             retVal += "\nHeight: " + QString::number(((Box)ao).getHeight());
             retVal += "\nDepth: " + QString::number(((Box)ao).getDepth());
         }
         else if(geoName == "sphere")
         {
             retVal += "\nName: " +((Sphere)ao).getName();
             retVal += "\nRadius: " + QString::number(((Sphere)ao).getSphereRadius());
         }
         retVal += "\n\nMaterial:\nName:" + ((Visual)(visual.at(i))).getMaterial().getName() + "\n";
         retVal += "Color: \nR:";
         retVal += QString::number(((Visual)(visual.at(i))).getMaterial().getColor().getRed()) + "\n";
         retVal += "Green: " + QString::number(((Visual)(visual.at(i))).getMaterial().getColor().getGreen()) + "\n";
         retVal += "Blue: " + QString::number(((Visual)(visual.at(i))).getMaterial().getColor().getBlue()) + "\n";
         retVal += "Alpha: " + QString::number(((Visual)(visual.at(i))).getMaterial().getColor().getAlpha()) + "\n";
     }
     retVal+="\n**************************************\n";


    return retVal;
}


