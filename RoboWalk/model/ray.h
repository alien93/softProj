#ifndef RAY_H
#define RAY_H

#include "horizontalray.h"
#include "verticalray.h"

class Ray
{
private:
    HorizontalRay hRay;
    VerticalRay vRay;
public:
    Ray();
    Ray(HorizontalRay hRay, VerticalRay vRay);

    HorizontalRay getHRay() const;
    void setHRay(const HorizontalRay &value);
    VerticalRay getVRay() const;
    void setVRay(const VerticalRay &value);
};

#endif // RAY_H
