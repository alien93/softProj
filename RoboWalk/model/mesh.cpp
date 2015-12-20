#include "mesh.h"

QString Mesh::getFilePath() const
{
    return filePath;
}

void Mesh::setFilePath(const QString &value)
{
    filePath = value;
}

double Mesh::getScale() const
{
    return scale;
}

void Mesh::setScale(double value)
{
    scale = value;
}

Mesh::Mesh()
{
    
}

Mesh::Mesh(QString filePath, double scale)
{
    this->filePath = filePath;
    this->scale = scale;
}
