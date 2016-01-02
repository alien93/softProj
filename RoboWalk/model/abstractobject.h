#ifndef ABSTRACTOBJECT_H
#define ABSTRACTOBJECT_H

#include <QString>

class AbstractObject
{
protected:
    QString name;
    double height;
    double width;
    double depth;
    double radius;
    double length;
    double sphereRadius;

public:
    explicit
    AbstractObject();
    AbstractObject(const AbstractObject& ao) {*this = ao;}
    QString getName() const;
    void setName(const QString &value);
    virtual ~AbstractObject(){}
    double getHeight() const;
    void setHeight(double value);
    double getWidth() const;
    void setWidth(double value);
    double getDepth() const;
    void setDepth(double value);
    double getRadius() const;
    void setRadius(double value);
    double getLength() const;
    void setLength(double value);
    double getSphereRadius() const;
    void setSphereRadius(double value);
};

#endif // ABSTRACTOBJECT_H
