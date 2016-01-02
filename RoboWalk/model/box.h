#ifndef BOX_H
#define BOX_H

#include "abstractobject.h"

class Box:public AbstractObject
{

public:
    Box();
    Box(const AbstractObject& ao):AbstractObject(ao){}
    Box(double height, double width, double depth);

    double getHeight() const;
    void setHeight(double value);
    double getWidth() const;
    void setWidth(double value);
    double getDepth() const;
    void setDepth(double value);
};

#endif // BOX_H
