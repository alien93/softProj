#include "calibration.h"

Calibration::Calibration()
{

}

Calibration::Calibration(double rising, double falling)
{
    this->rising = rising;
    this->falling = falling;
}

double Calibration::getRising() const
{
    return rising;
}

void Calibration::setRising(double value)
{
    rising = value;
}

double Calibration::getFalling() const
{
    return falling;
}

void Calibration::setFalling(double value)
{
    falling = value;
}


