#ifndef LIMIT_H
#define LIMIT_H


class Limit
{
private:
    double lower; //An attribute specifying the lower joint limit (radians for revolute joints, meters for prismatic joints). Omit if joint is continuous.
    double upper; //An attribute specifying the upper joint limit (radians for revolute joints, meters for prismatic joints). Omit if joint is continuous.
    double effort; //An attribute for enforcing the maximum joint effort (|applied effort| < |effort|)
    double velocity; //An attribute for enforcing the maximum joint velocity.
public:
    Limit();
    Limit(double lower, double upper,
          double effort, double velocity);


    double getLower() const;
    void setLower(double value);
    double getUpper() const;
    void setUpper(double value);
    double getEffort() const;
    void setEffort(double value);
    double getVelocity() const;
    void setVelocity(double value);
};

#endif // LIMIT_H
