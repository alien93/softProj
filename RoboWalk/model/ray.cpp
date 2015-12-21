#include "ray.h"

HorizontalRay Ray::getHRay() const
{
    return hRay;
}

void Ray::setHRay(const HorizontalRay &value)
{
    hRay = value;
}

VerticalRay Ray::getVRay() const
{
    return vRay;
}

void Ray::setVRay(const VerticalRay &value)
{
    vRay = value;
}

Ray::Ray()
{

}

Ray::Ray(HorizontalRay hRay, VerticalRay vRay)
{
    this->hRay = hRay;
    this->vRay = vRay;
}
