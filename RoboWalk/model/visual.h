#ifndef VISUAL_H
#define VISUAL_H

#include <QString>
#include "origin.h"
#include "geometry.h"
#include "material.h"

class Visual
{
private:
    QString name;
    Origin origin;
    Geometry geometry;
    Material material;
public:
    Visual();
    Visual(QString name, Origin origin,
           Geometry geometry, Material material);

    QString getName() const;
    void setName(const QString &value);
    Origin getOrigin() const;
    void setOrigin(const Origin &value);
    Geometry getGeometry() const;
    void setGeometry(const Geometry &value);
    Material getMaterial() const;
    void setMaterial(const Material &value);
};

#endif // VISUAL_H
