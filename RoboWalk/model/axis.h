#ifndef AXIS_H
#define AXIS_H


class Axis
{
private:
    //xyz - Represents the x, y, z components of a vector. The vector should be normalized.
    double x;
    double y;
    double z;

    double r;
    double p;
    double yy;

public:
    Axis();
    Axis(double x, double y, double z,
         double r, double p, double yy);


    double getX() const;
    void setX(double value);
    double getY() const;
    void setY(double value);
    double getZ() const;
    void setZ(double value);
    double getR() const;
    void setR(double value);
    double getP() const;
    void setP(double value);
    double getYy() const;
    void setYy(double value);
};

#endif // AXIS_H
