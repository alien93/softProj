#ifndef ABSTRACTOBJECT_H
#define ABSTRACTOBJECT_H

#include <QString>

class AbstractObject
{
private:
    QString name;
public:
    AbstractObject();
    QString getName() const;
    void setName(const QString &value);
};

#endif // ABSTRACTOBJECT_H
