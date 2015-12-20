#ifndef JOINT_H
#define JOINT_H

#include <QString>
#include "origin.h"
#include "parent.h"
#include "child.h"
#include "axis.h"
#include "calibration.h"
#include "dynamics.h"
#include "limit.h"
#include "mimic.h"
#include "safetycontroller.h"

enum Types {revolute, continuous, prismatic, fixed, floating, planar};

class Joint
{
private:
    QString name; //name of the joint
    Types type;   //the type of joint
    Origin origin;
    Parent parent;
    Child child;
    Axis axis;
    Calibration calibration;
    Dynamics dynamics;
    Limit limit;
    Mimic mimic;
    SafetyController safetyController;

public:
    Joint();
    Joint( QString name,
           Types type,
           Origin origin,
           Parent parent,
           Child child,
           Axis axis,
           Calibration calibration,
           Dynamics dynamics,
           Limit limit,
           Mimic mimic,
           SafetyController safetyController);

    QString getName() const;
    void setName(const QString &value);
    Types getType() const;
    void setType(const Types &value);
    Origin getOrigin() const;
    void setOrigin(const Origin &value);
    Parent getParent() const;
    void setParent(const Parent &value);
    Child getChild() const;
    void setChild(const Child &value);
    Axis getAxis() const;
    void setAxis(const Axis &value);
    Calibration getCalibration() const;
    void setCalibration(const Calibration &value);
    Dynamics getDynamics() const;
    void setDynamics(const Dynamics &value);
    Limit getLimit() const;
    void setLimit(const Limit &value);
    Mimic getMimic() const;
    void setMimic(const Mimic &value);
    SafetyController getSafetyController() const;
    void setSafetyController(const SafetyController &value);
};

#endif // JOINT_H
