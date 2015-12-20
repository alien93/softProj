#include "limit.h"

Limit::Limit()
{

}

Limit::Limit(double lower, double upper,
             double effort, double velocity)
{
    this->lower = lower;
    this->upper = upper;
    this->effort = effort;
    this->velocity = velocity;
}

double Limit::getLower() const
{
    return lower;
}

void Limit::setLower(double value)
{
    lower = value;
}

double Limit::getUpper() const
{
    return upper;
}

void Limit::setUpper(double value)
{
    upper = value;
}

double Limit::getEffort() const
{
    return effort;
}

void Limit::setEffort(double value)
{
    effort = value;
}

double Limit::getVelocity() const
{
    return velocity;
}

void Limit::setVelocity(double value)
{
    velocity = value;
}


