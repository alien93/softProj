#ifndef LINK_H
#define LINK_H

#include <QString>
#include "visual.h"
#include "inertial.h"
#include "collision.h"

class Link
{
private:
    QString name;
    Inertial inertial;
    Visual visual;
    Collision collision;
public:
    Link();
    Link(QString name, Inertial inertial, Visual visual, Collision collision);


    QString getName() const;
    void setName(const QString &value);
    Inertial getInertial() const;
    void setInertial(const Inertial &value);
    Visual getVisual() const;
    void setVisual(const Visual &value);
    Collision getCollision() const;
    void setCollision(const Collision &value);
};

#endif // LINK_H
