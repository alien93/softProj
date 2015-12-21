#include "texture.h"

QString Texture::getFilePath() const
{
    return filePath;
}

void Texture::setFilePath(const QString &value)
{
    filePath = value;
}

Texture::Texture()
{
    
}

Texture::Texture(QString filePath)
{
    this->filePath = filePath;
}
