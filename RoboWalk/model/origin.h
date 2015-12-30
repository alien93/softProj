#ifndef ORIGIN_H
#define ORIGIN_H


class Origin
{
private:
    //xyz Represents the x, y, z offset.
    double xyz_x;
    double xyz_y;
    double xyz_z;
    //rpy Represents the rotation around fixed axis: first roll around x,
    //then pitch around y and finally yaw around z. All angles are specified in radians.
    double rpy_r;
    double rpy_p;
    double rpy_y;
public:
    Origin();
    Origin(double xyz_x, double xyz_y, double xyz_z,
           double rpy_r, double rpy_p, double rpy_y);

    double getXyz_x() const;
    void setXyz_x(double value);
    double getXyz_y() const;
    void setXyz_y(double value);
    double getXyz_z() const;
    void setXyz_z(double value);
    double getRpy_r() const;
    void setRpy_r(double value);
    double getRpy_p() const;
    void setRpy_p(double value);
    double getRpy_y() const;
    void setRpy_y(double value);
};

#endif // ORIGIN_H
