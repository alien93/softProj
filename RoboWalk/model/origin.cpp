#include "origin.h"

Origin::Origin()
{

}

Origin:: Origin(int xyz_x, int xyz_y, int xyz_z,
                double rpy_r, double rpy_p, double rpy_y)
{
    this->xyz_x = xyz_x;
    this->xyz_y = xyz_y;
    this->xyz_z = xyz_z;
    this->rpy_r = rpy_y;
    this->rpy_p = rpy_p;
    this->rpy_y = rpy_y;
}


int Origin::getXyz_x() const
{
    return xyz_x;
}

void Origin::setXyz_x(int value)
{
    xyz_x = value;
}

int Origin::getXyz_y() const
{
    return xyz_y;
}

void Origin::setXyz_y(int value)
{
    xyz_y = value;
}

int Origin::getXyz_z() const
{
    return xyz_z;
}

void Origin::setXyz_z(int value)
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


