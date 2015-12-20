#ifndef SAFETYCONTROLLER_H
#define SAFETYCONTROLLER_H


class SafetyController
{
private:
    //An attribute specifying the lower joint boundary where the safety
    //controller starts limiting the position of the joint. This limit needs
    //to be larger than the lower joint limit (see above).
    double softLowerLimit;

    //An attribute specifying the upper joint boundary where the safety
    //controller starts limiting the position of the joint. This limit needs
    //to be smaller than the upper joint limit (see above).
    double softUpperLimit;

    //An attribute specifying the relation between position and velocity limits.
    double kPosition;

    //An attribute specifying the relation between effort and velocity limits.
    double kVelocity;

public:
    SafetyController();
    SafetyController(double softLowerLimit, double softUpperLimit,
                     double kPosition, double kVelocity);


    double getSoftLowerLimit() const;
    void setSoftLowerLimit(double value);
    double getSoftUpperLimit() const;
    void setSoftUpperLimit(double value);
    double getKPosition() const;
    void setKPosition(double value);
    double getKVelocity() const;
    void setKVelocity(double value);
};

#endif // SAFETYCONTROLLER_H
