#ifndef CHILD_H
#define CHILD_H

#include <QString>

class Child
{
private:
    QString link;
public:
    Child();
    Child(QString link);


    QString getLink() const;
    void setLink(const QString &value);
};

#endif // CHILD_H
