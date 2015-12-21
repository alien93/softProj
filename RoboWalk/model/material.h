#ifndef MATERIAL_H
#define MATERIAL_H

#include <QString>
#include "color.h"
#include "texture.h"

class Material
{
private:
    QString name;
    Color color;
    Texture texture;
public:
    Material();
    Material(QString name, Color color, Texture texture);

    QString getName() const;
    Color getColor() const;
    void setColor(const Color &value);
    Texture getTexture() const;
    void setTexture(const Texture &value);
};

#endif // MATERIAL_H
