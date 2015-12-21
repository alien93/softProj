#ifndef SENSOR_H
#define SENSOR_H

#include <QString>
#include "parent.h"
#include "origin.h"
#include "camera.h"
#include "ray.h"

class Sensor
{
private:
    QString name;
    float updateRate; //Hz
    Parent parent;
    Origin origin;
    Camera camera;
    Ray ray;
public:
    Sensor();
    Sensor(QString name, float updateRate,
           Parent parent, Origin origin,
           Camera camera, Ray ray);

    QString getName() const;
    void setName(const QString &value);
    float getUpdateRate() const;
    void setUpdateRate(float value);
    Parent getParent() const;
    void setParent(const Parent &value);
    Origin getOrigin() const;
    void setOrigin(const Origin &value);
    Camera getCamera() const;
    void setCamera(const Camera &value);
    Ray getRay() const;
    void setRay(const Ray &value);
};

#endif // SENSOR_H
