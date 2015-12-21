#include "material.h"

QString Material::getName() const
{
    return name;
}

Color Material::getColor() const
{
    return color;
}

void Material::setColor(const Color &value)
{
    color = value;
}

Texture Material::getTexture() const
{
    return texture;
}

void Material::setTexture(const Texture &value)
{
    texture = value;
}

Material::Material()
{
    
}

Material::Material(QString name, Color color, Texture texture)
{
    this->name = name;
    this->color = color;
    this->texture = texture;
}
