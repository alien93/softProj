#include "joint.h"

Joint::Joint()
{

}

Joint::Joint( QString name,
       Types type,
       Origin origin,
       Parent parent,
       Child child,
       Axis axis,
       Calibration calibration,
       Dynamics dynamics,
       Limit limit,
       Mimic mimic,
       SafetyController safetyController)
{
    this->name = name;
    this->type = type;
    this->origin = origin;
    this->parent = parent;
    this->child = child;
    this->axis = axis;
    this->calibration = calibration;
    this->dynamics = dynamics;
    this->limit = limit;
    this->mimic = mimic;
    this->safetyController = safetyController;
}

QString Joint::getName() const
{
    return name;
}

void Joint::setName(const QString &value)
{
    name = value;
}

Types Joint::getType() const
{
    return type;
}

void Joint::setType(const Types &value)
{
    type = value;
}

Origin Joint::getOrigin() const
{
    return origin;
}

void Joint::setOrigin(const Origin &value)
{
    origin = value;
}

Parent Joint::getParent() const
{
    return parent;
}

void Joint::setParent(const Parent &value)
{
    parent = value;
}

Child Joint::getChild() const
{
    return child;
}

void Joint::setChild(const Child &value)
{
    child = value;
}

Axis Joint::getAxis() const
{
    return axis;
}

void Joint::setAxis(const Axis &value)
{
    axis = value;
}

Calibration Joint::getCalibration() const
{
    return calibration;
}

void Joint::setCalibration(const Calibration &value)
{
    calibration = value;
}

Dynamics Joint::getDynamics() const
{
    return dynamics;
}

void Joint::setDynamics(const Dynamics &value)
{
    dynamics = value;
}

Limit Joint::getLimit() const
{
    return limit;
}

void Joint::setLimit(const Limit &value)
{
    limit = value;
}

Mimic Joint::getMimic() const
{
    return mimic;
}

void Joint::setMimic(const Mimic &value)
{
    mimic = value;
}

SafetyController Joint::getSafetyController() const
{
    return safetyController;
}

void Joint::setSafetyController(const SafetyController &value)
{
    safetyController = value;
}
