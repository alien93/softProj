#ifndef TEXTURE_H
#define TEXTURE_H

#include <QString>

class Texture
{
private:
    QString filePath;
public:
    Texture();
    Texture(QString filePath);

    QString getFilePath() const;
    void setFilePath(const QString &value);
};

#endif // TEXTURE_H
