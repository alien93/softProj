#include "color.h"

double Color::getRed() const
{
    return red;
}

void Color::setRed(double value)
{
    red = value;
}

double Color::getGreen() const
{
    return green;
}

void Color::setGreen(double value)
{
    green = value;
}

double Color::getBlue() const
{
    return blue;
}

void Color::setBlue(double value)
{
    blue = value;
}

double Color::getAlpha() const
{
    return alpha;
}

void Color::setAlpha(double value)
{
    alpha = value;
}

Color::Color()
{
    
}

Color::Color(double red, double green, double blue, double alpha)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = alpha;
}
