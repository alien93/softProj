#include "safetycontroller.h"

SafetyController::SafetyController()
{

}

SafetyController::SafetyController(double softLowerLimit, double softUpperLimit,
                                   double kPosition, double kVelocity)
{
    this->softLowerLimit = softLowerLimit;
    this->softUpperLimit = softUpperLimit;
    this->kPosition = kPosition;
    this->kVelocity = kVelocity;
}

double SafetyController::getSoftLowerLimit() const
{
    return softLowerLimit;
}

void SafetyController::setSoftLowerLimit(double value)
{
    softLowerLimit = value;
}

double SafetyController::getSoftUpperLimit() const
{
    return softUpperLimit;
}

void SafetyController::setSoftUpperLimit(double value)
{
    softUpperLimit = value;
}

double SafetyController::getKPosition() const
{
    return kPosition;
}

void SafetyController::setKPosition(double value)
{
    kPosition = value;
}

double SafetyController::getKVelocity() const
{
    return kVelocity;
}

void SafetyController::setKVelocity(double value)
{
    kVelocity = value;
}

