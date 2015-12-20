#include "inertia.h"

double Inertia::getIxx() const
{
    return ixx;
}

void Inertia::setIxx(double value)
{
    ixx = value;
}

double Inertia::getIxy() const
{
    return ixy;
}

void Inertia::setIxy(double value)
{
    ixy = value;
}

double Inertia::getIxz() const
{
    return ixz;
}

void Inertia::setIxz(double value)
{
    ixz = value;
}

double Inertia::getIyy() const
{
    return iyy;
}

void Inertia::setIyy(double value)
{
    iyy = value;
}

double Inertia::getIyz() const
{
    return iyz;
}

void Inertia::setIyz(double value)
{
    iyz = value;
}

double Inertia::getIzz() const
{
    return izz;
}

void Inertia::setIzz(double value)
{
    izz = value;
}

Inertia::Inertia()
{
    
}

Inertia::Inertia(double ixx, double ixy, double ixz, double iyy, double iyz, double izz)
{
    this->ixx = ixx;
    this->ixy = ixy;
    this->ixz = ixz;
    this->iyy = iyy;
    this->iyz = iyz;
    this->izz = izz;
}
