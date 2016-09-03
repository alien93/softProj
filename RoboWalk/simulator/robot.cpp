#include "robot.h"


QString Robot::jointName = "";

double Robot::getLimit() const
{
    return limit;
}

void Robot::setLimit(double value)
{
    limit = value;
}

Robot::Robot(World* world, dReal posX, dReal posY, dReal posZ)
    :ObjectODE(true, posX, posY, posZ)
{
    this->w = world;
    this->limit = 0.1;
}

Robot::~Robot()
{

}


ObjectODE* Robot::draw(Link l)
{
    vector<Visual> visuals = l.getVisual();
    if(visuals.size()>0)
    {
        for(vector<Visual>::iterator it=visuals.begin(); it!=visuals.end(); it++)
        {
            Origin o = it->getOrigin();
            Geometry g = it->getGeometry();
            Material m = it->getMaterial();

            if(g.getObject().getName() == "cylinder")
            {
                double length = g.getObject().getLength();
                double radius = g.getObject().getRadius();
                double r = o.getRpy_r();
                double p = o.getRpy_p();
                double yy = o.getRpy_y();
                double x = o.getXyz_x();
                double y = o.getXyz_y();
                double z = o.getXyz_z();
                double red = m.getColor().getRed();
                double green = m.getColor().getGreen();
                double blue = m.getColor().getBlue();
                double alpha = m.getColor().getAlpha();

                cylinder = new DrawCylinder(w, true, length, radius,
                                            r, p, yy,
                                            x, y, z,
                                            red, green, blue, alpha);
                cylinder->draw();
                return cylinder;
            }
            else if(g.getObject().getName() == "box")
            {
                double width = g.getObject().getWidth();
                double height = g.getObject().getHeight();
                double depth = g.getObject().getDepth();
                double r = o.getRpy_r();
                double p = o.getRpy_p();
                double yy = o.getRpy_y();
                double x = o.getXyz_x();
                double y = o.getXyz_y();
                double z = o.getXyz_z();
                double red = m.getColor().getRed();
                double green = m.getColor().getGreen();
                double blue = m.getColor().getBlue();
                double alpha = m.getColor().getAlpha();

                box = new DrawBox(w, true, width, height, depth,
                                  r, p, yy,
                                  x, y, z,
                                  red, green, blue, alpha);
                box->draw();
                return box;
            }
            else if(g.getObject().getName() == "sphere")
            {
                double radius = g.getObject().getSphereRadius();
                double r = o.getRpy_r();
                double p = o.getRpy_p();
                double yy = o.getRpy_y();
                double x = o.getXyz_x();
                double y = o.getXyz_y();
                double z = o.getXyz_z();
                double red = m.getColor().getRed();
                double green = m.getColor().getGreen();
                double blue = m.getColor().getBlue();
                double alpha = m.getColor().getAlpha();

                sphere = new DrawSphere(w, true,  radius,
                                        r, p, yy,
                                        x, y, z,
                                        red, green, blue, alpha);
                sphere->draw();
                return sphere;
            }
        }
    }
    return NULL;
}

void Robot::rotateMe(double r, double p, double y)
{
    double angle = 0;
    if(r!=0)
    {
        angle = convertRadToDegrees(r);
        r = 1;
    }
    if(p!=0)
    {
        angle = convertRadToDegrees(p);
        p = 1;
    }
    if(y!=0)
    {
        angle = convertRadToDegrees(y);
        y = 1;
    }
    glRotated(angle, r, p, y);
}

double Robot::convertRadToDegrees(double value)
{
    double retVal;
    retVal = value * 180 / M_PI;
    return retVal;
}

void Robot::setPosition(Point3 newPosition)
{

}

Point3 Robot::getPosition()
{

}

void Robot::setOrientation(int axis, dReal angle)
{

}

void Robot::draw()
{
    map<QString, Link> linksMap = parser->getInstance()->rm.getLinks();
    vector<Link> links = parser->getInstance()->rm.getLinksVector();
    map<QString, Joint> jointsMap = parser->getInstance()->rm.getJoints();
    vector<Joint> joints = parser->getInstance()->rm.sortJoints(jointsMap);

    if(joints.size()!=0)
    {
        for(vector<Joint>::iterator it=joints.begin(); it!=joints.end(); it++)
        {
            Joint j = *it;
            Parent p = j.getParent();   //parent
            Child c = j.getChild();     //child
            Origin o = j.getOrigin();   //position of the child link relative to parent link

            //draw parent link
            Link lp = linksMap.at(p.getLink());
            map<QString, Link> usedLinks = parser->getInstance()->getUsedLinks();

            if(usedLinks.count(lp.getName()))
            {
                //the link already exists
                glLoadMatrixf(matrices.at(lp.getName()));
            }
            else
            {
                glGetFloatv (GL_MODELVIEW_MATRIX, m);
                for(int i=0; i<16; i++)
                {
                    matrices[lp.getName()][i] = m[i];
                }
                usedLinks[lp.getName()] = lp;
                parser->getInstance()->setUsedLinks(usedLinks);
                elem1 = draw(lp);
            }

            //joint transformations
            if(jointName!="" && j.getChild().getLink()==jointName)
            {
                Axis axis = j.getAxis();
                glTranslated(o.getXyz_x(), o.getXyz_y(), o.getXyz_z());
                rotateMe(limit*(axis.getX()), limit*(axis.getY()), limit*(axis.getZ()));

            }
            else
            {
                glTranslated(o.getXyz_x(), o.getXyz_y(), o.getXyz_z());
                rotateMe(o.getRpy_r(), o.getRpy_p(), o.getRpy_y());
            }


            //draw child link
            Link lc = linksMap.at(c.getLink());
            elem2 = draw(lc);


            //create joints
            if(elem1 != NULL && elem2 != NULL)
            {
                dJointID joint = dJointCreateHinge(w->getWorldID(), 0);
                dJointAttach(joint, elem1->getBodyID(), elem2->getBodyID());
                Point3 jointPoint = {(dReal)j.getOrigin().getXyz_x(), (dReal)j.getOrigin().getXyz_y(), (dReal)j.getOrigin().getXyz_z()};
                dJointSetHingeAnchor(joint, jointPoint.x, jointPoint.y, jointPoint.z);
                dJointSetHingeAxis(joint, 1, 0, 0);
                dJointSetHingeParam(joint, dParamLoStop, j.getLimit().getLower());
                dJointSetHingeParam(joint, dParamHiStop, j.getLimit().getUpper());
            }
        }
        map<QString, Link> newMap = parser->getInstance()->getUsedLinks();
        newMap.clear();
        matrices.clear();
        parser->getInstance()->setUsedLinks(newMap);
    }
    else

        //single link, no joints
        for(vector<Link>::iterator it=links.begin(); it!=links.end(); it++)
        {
            glPushMatrix();
            Link lp = *it;
            draw(lp);
            glPopMatrix();
        }
}
