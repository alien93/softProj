#ifndef MESH_H
#define MESH_H

#include "abstractobject.h"
#include <QString>

class Mesh:public AbstractObject
{
private:
    QString filePath;
    double scale;
public:
    Mesh();
    Mesh(QString filePath, double scale);


    QString getFilePath() const;
    void setFilePath(const QString &value);
    double getScale() const;
    void setScale(double value);
};

#endif // MESH_H
