#ifndef CAMERA_H
#define CAMERA_H

#include "image.h"

class Camera
{
private:
    Image image;
public:
    Camera();
    Camera(Image image);


    Image getImage() const;
    void setImage(const Image &value);
};

#endif // CAMERA_H
