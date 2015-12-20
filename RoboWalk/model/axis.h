#ifndef AXIS_H
#define AXIS_H


class Axis
{
private:
    //xyz - Represents the x, y, z components of a vector. The vector should be normalized.
    int x;
    int y;
    int z;
public:
    Axis();
    Axis(int x, int y, int z);


    int getX() const;
    void setX(int value);
    int getY() const;
    void setY(int value);
    int getZ() const;
    void setZ(int value);
};

#endif // AXIS_H
