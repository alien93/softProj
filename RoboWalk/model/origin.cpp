#include "origin.h"

Origin::Origin()
{

}

Origin:: Origin(double xyz_x, double xyz_y, double xyz_z,
                double rpy_r, double rpy_p, double rpy_y)
{
    this->xyz_x = xyz_x;
    this->xyz_y = xyz_y;
    this->xyz_z = xyz_z;
    this->rpy_r = rpy_r;
    this->rpy_p = rpy_p;
    this->rpy_y = rpy_y;
}


double Origin::getXyz_x() const
{
    return xyz_x;
}

void Origin::setXyz_x(double value)
{
    xyz_x = value;
}

double Origin::getXyz_y() const
{
    return xyz_y;
}

void Origin::setXyz_y(double value)
{
    xyz_y = value;
}

double Origin::getXyz_z() const
{
    return xyz_z;
}

void Origin::setXyz_z(double value)
{
    xyz_z = value;
}

double Origin::getRpy_r() const
{
    return rpy_r;
}

void Origin::setRpy_r(double value)
{
    rpy_r = value;
}

double Origin::getRpy_p() const
{
    return rpy_p;
}

void Origin::setRpy_p(double value)
{
    rpy_p = value;
}

double Origin::getRpy_y() const
{
    return rpy_y;
}

void Origin::setRpy_y(double value)
{
    rpy_y = value;
}


