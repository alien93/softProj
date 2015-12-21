#include "horizontalray.h"

unsigned int HorizontalRay::getSamples() const
{
    return samples;
}

void HorizontalRay::setSamples(unsigned int value)
{
    samples = value;
}

float HorizontalRay::getResolution() const
{
    return resolution;
}

void HorizontalRay::setResolution(float value)
{
    resolution = value;
}

float HorizontalRay::getMinAngle() const
{
    return minAngle;
}

void HorizontalRay::setMinAngle(float value)
{
    minAngle = value;
}

float HorizontalRay::getMaxAngle() const
{
    return maxAngle;
}

void HorizontalRay::setMaxAngle(float value)
{
    maxAngle = value;
}

HorizontalRay::HorizontalRay()
{
    
}

HorizontalRay::HorizontalRay(unsigned int samples, float resolution, float minAngle, float maxAngle)
{
    this->samples = samples;
    this->resolution = resolution;
    this->minAngle = minAngle;
    this->maxAngle = maxAngle;
}
