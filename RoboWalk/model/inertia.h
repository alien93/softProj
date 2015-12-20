#ifndef INERTIA_H
#define INERTIA_H

/*
The 3x3 rotational inertia matrix, represented in the inertia frame.
Because the rotational inertia matrix is symmetric, only 6 above-diagonal
elements of this matrix are specified here, using the attributes ixx, ixy, ixz, iyy, iyz, izz.
*/

class Inertia
{
private:
    double ixx;
    double ixy;
    double ixz;
    double iyy;
    double iyz;
    double izz;
public:
    Inertia();
    Inertia(double ixx, double ixy, double ixz,
            double iyy, double iyz, double izz);


    double getIxx() const;
    void setIxx(double value);
    double getIxy() const;
    void setIxy(double value);
    double getIxz() const;
    void setIxz(double value);
    double getIyy() const;
    void setIyy(double value);
    double getIyz() const;
    void setIyz(double value);
    double getIzz() const;
    void setIzz(double value);
};

#endif // INERTIA_H
