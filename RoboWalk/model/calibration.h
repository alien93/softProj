#ifndef CALIBRATION_H
#define CALIBRATION_H


class Calibration
{
private:
    double rising; //When the joint moves in a positive direction, this reference position will trigger a rising edge.
    double falling; //When the joint moves in a positive direction, this reference position will trigger a falling edge.
public:
    Calibration();
    Calibration(double rising, double falling);


    double getRising() const;
    void setRising(double value);
    double getFalling() const;
    void setFalling(double value);
};

#endif // CALIBRATION_H
