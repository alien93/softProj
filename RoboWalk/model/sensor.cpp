#include "sensor.h"

QString Sensor::getName() const
{
    return name;
}

void Sensor::setName(const QString &value)
{
    name = value;
}

float Sensor::getUpdateRate() const
{
    return updateRate;
}

void Sensor::setUpdateRate(float value)
{
    updateRate = value;
}

Parent Sensor::getParent() const
{
    return parent;
}

void Sensor::setParent(const Parent &value)
{
    parent = value;
}

Origin Sensor::getOrigin() const
{
    return origin;
}

void Sensor::setOrigin(const Origin &value)
{
    origin = value;
}

Camera Sensor::getCamera() const
{
    return camera;
}

void Sensor::setCamera(const Camera &value)
{
    camera = value;
}

Ray Sensor::getRay() const
{
    return ray;
}

void Sensor::setRay(const Ray &value)
{
    ray = value;
}

Sensor::Sensor()
{

}

Sensor::Sensor(QString name, float updateRate, Parent parent, Origin origin, Camera camera, Ray ray)
{
    this->name = name;
    this->updateRate = updateRate;
    this->parent = parent;
    this->origin = origin;
    this->camera = camera;
    this->ray = ray;
}
