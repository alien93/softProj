#include "image.h"

unsigned int Image::getWidth() const
{
    return width;
}

void Image::setWidth(unsigned int value)
{
    width = value;
}

unsigned int Image::getHeight() const
{
    return height;
}

void Image::setHeight(unsigned int value)
{
    height = value;
}

QString Image::getFormat() const
{
    return format;
}

void Image::setFormat(const QString &value)
{
    format = value;
}

float Image::getHfov() const
{
    return hfov;
}

void Image::setHfov(float value)
{
    hfov = value;
}

float Image::getNear() const
{
    return near;
}

void Image::setNear(float value)
{
    near = value;
}

float Image::getFar() const
{
    return far;
}

void Image::setFar(float value)
{
    far = value;
}

Image::Image()
{
    
}

Image::Image(unsigned int width, unsigned int height, QString format, float hfov, float near, float far)
{
    this->width = width;
    this->height = height;
    this->format = format;
    this->hfov = hfov;
    this->near = near;
    this->far = far;
}
