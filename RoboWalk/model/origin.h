#ifndef ORIGIN_H
#define ORIGIN_H


class Origin
{
private:
    //xyz Represents the x, y, z offset.
    int xyz_x;
    int xyz_y;
    int xyz_z;
    //rpy Represents the rotation around fixed axis: first roll around x,
    //then pitch around y and finally yaw around z. All angles are specified in radians.
    double rpy_r;
    double rpy_p;
    double rpy_y;
public:
    Origin();
    Origin(int xyz_x, int xyz_y, int xyz_z,
           double rpy_r, double rpy_p, double rpy_y);

    int getXyz_x() const;
    void setXyz_x(int value);
    int getXyz_y() const;
    void setXyz_y(int value);
    int getXyz_z() const;
    void setXyz_z(int value);
    double getRpy_r() const;
    void setRpy_r(double value);
    double getRpy_p() const;
    void setRpy_p(double value);
    double getRpy_y() const;
    void setRpy_y(double value);
};

#endif // ORIGIN_H
