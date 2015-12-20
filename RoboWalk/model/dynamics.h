#ifndef DYNAMICS_H
#define DYNAMICS_H


class Dynamics
{
private:
    double damping; //the physical damping value of the joing (N*s/m for prismatic joints, N*m*s/rad for revolute joints)
    double friction; //the physical static friction value of the joint (N for prismatic joints, N*m for revolute joints)
public:
    Dynamics();
    Dynamics (double damping, double friction);
    double getDamping() const;
    void setDamping(double value);
    double getFriction() const;
    void setFriction(double value);
};

#endif // DYNAMICS_H
