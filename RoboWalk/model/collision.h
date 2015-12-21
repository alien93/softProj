#ifndef COLLISION_H
#define COLLISION_H

#include <QString>
#include "origin.h"
#include "geometry.h"

class Collision
{
private:
    //Specifies a name for a part of a link's geometry.
    //This is useful to be able to refer to specific bits of the geometry of a link.
    QString name;
    Origin origin;
    Geometry geometry;
public:
    Collision();
    Collision(QString name, Origin origin, Geometry geometry);

    QString getName() const;
    void setName(const QString &value);
    Origin getOrigin() const;
    void setOrigin(const Origin &value);
    Geometry getGeometry() const;
    void setGeometry(const Geometry &value);
};

#endif // COLLISION_H
