#ifndef IMAGE_H
#define IMAGE_H

#include <QString>

class Image
{
private:
    unsigned int width; //pixels
    unsigned int height; //pixels
    QString format; //image format of the camera
    float hfov; //radians, horizontal field of view of the camera
    float near; //m, near clip distance of the camera in meters
    float far; //m, far clip distance of the camera in meters. This needs to be greater or equal to near clip
public:
    Image();
    Image(unsigned int width, unsigned int height,
          QString format, float hfov, float near,
          float far);


    unsigned int getWidth() const;
    void setWidth(unsigned int value);
    unsigned int getHeight() const;
    void setHeight(unsigned int value);
    QString getFormat() const;
    void setFormat(const QString &value);
    float getHfov() const;
    void setHfov(float value);
    float getNear() const;
    void setNear(float value);
    float getFar() const;
    void setFar(float value);
};

#endif // IMAGE_H
