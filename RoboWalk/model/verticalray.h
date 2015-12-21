#ifndef VERTICALRAY_H
#define VERTICALRAY_H


class VerticalRay
{
private:
    unsigned int samples;
    float resolution;
    float minAngle;
    float maxAngle;
public:
    VerticalRay();
    VerticalRay(unsigned int samples, float resolution,
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

#endif // VERTICALRAY_H
