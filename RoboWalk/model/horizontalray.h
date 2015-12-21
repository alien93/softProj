#ifndef HORIZONTALRAY_H
#define HORIZONTALRAY_H


class HorizontalRay
{
private:
    unsigned int samples; //The number of simulated rays to generate per complete laser sweep cycle.

    //This number is multiplied by samples to determine the number
    //of range data points returned. If resolution is less than one,
    //range data is interpolated. If resolution is greater than one, range data is averaged.
    float resolution;

    float minAngle; //rad
    float maxAngle; //rad
public:
    HorizontalRay();
    HorizontalRay(unsigned int samples, float resolution,
                  float minAngle, float maxAngle);

    unsigned int getSamples() const;
    void setSamples(unsigned int value);
    float getResolution() const;
    void setResolution(float value);
    float getMinAngle() const;
    void setMinAngle(float value);
    float getMaxAngle() const;
    void setMaxAngle(float value);
};

#endif // HORIZONTALRAY_H
