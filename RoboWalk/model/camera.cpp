#include "camera.h"

Image Camera::getImage() const
{
    return image;
}

void Camera::setImage(const Image &value)
{
    image = value;
}

Camera::Camera()
{

}

Camera::Camera(Image image)
{
    this->image = image;
}
