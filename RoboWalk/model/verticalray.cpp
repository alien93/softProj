#include "verticalray.h"

unsigned int VerticalRay::getSamples() const
{
    return samples;
}

void VerticalRay::setSamples(unsigned int value)
{
    samples = value;
}

float VerticalRay::getResolution() const
{
    return resolution;
}

void VerticalRay::setResolution(float value)
{
    resolution = value;
}

float VerticalRay::getMinAngle() const
{
    return minAngle;
}

void VerticalRay::setMinAngle(float value)
{
    minAngle = value;
}

float VerticalRay::getMaxAngle() const
{
    return maxAngle;
}

void VerticalRay::setMaxAngle(float value)
{
    maxAngle = value;
}

VerticalRay::VerticalRay()
{
    
}
